//
//  GSNavMesh.cpp
//  GSPathFind
//
//  Created by Can Wu on 2017/7/28.
//
//

#include "GSNavMesh.hpp"
#include "GSNavLog.hpp"
#include "GSNavMath.hpp"
#include "GSNavTriangulator.hpp"
#include "GSNavLog.hpp"
#include <algorithm>
#include <limits.h>

///GSNavMesh
GSNavMesh::GSNavMesh()
{
    
}

GSNavMesh::~GSNavMesh()
{
    
}

void GSNavMesh::init(const GSPolygon& polygon)
{
    
    m_navObstacles.clear();
    m_polygons.clear();
    m_gspolygons.clear();
    m_connections.clear();
    
    next_obstacle_Id = 0;
    this->m_state = GSNavMeshState::eNormal;
    
    GSID id;
    this->addObstacle(polygon.points, id);
}

void GSNavMesh::update(int dt)
{
    if(this->m_state == GSNavMeshState::eNormal){
        return;
    }
    
    this->m_state = GSNavMeshState::eNormal;
    
    m_gspolygons.clear();
    
    std::vector<TriangulatorPoly> in_Triangulator,out_triangulator;
    
    std::vector<GSNavObstacle> &obstacles = m_navObstacles;
    //calculate outside
//    GSNavPoint outside_point(0,0);
//    
//    for(size_t obstacleIndex = 0 ; obstacleIndex < obstacles.size(); obstacleIndex++){
//        GSNavObstacle &obstacle = obstacles[obstacleIndex];
//        std::vector<GSNavPoint> &points = obstacle.polygon.points;
//        int pointsCount = points.size();
//        
//        for(int j = 0 ; j < pointsCount; j++){
//            outside_point.x = std::max(outside_point.x, points[j].x);
//            outside_point.y = std::max(outside_point.y, points[j].y);
//        }
//    }
    
    //generate polygon
    for(size_t obstacleIndex = 0 ; obstacleIndex < obstacles.size(); obstacleIndex++){
        GSNavObstacle &obstacle = obstacles[obstacleIndex];
        std::vector<GSNavPoint> &points = obstacle.polygon.points;
        int pointsCount = points.size();
        
        int interscount = 0;
        
        for(size_t obstacleIndex2 = 0 ; obstacleIndex2 < obstacles.size(); obstacleIndex2++){
            if(obstacleIndex2 == obstacleIndex){
                continue;
            }
            
            GSNavObstacle &obstacle2 = obstacles[obstacleIndex2];
            std::vector<GSNavPoint> &points2 = obstacle2.polygon.points;
            int pointsCount2 = points2.size();
            
            for(size_t l = 0 ; l < pointsCount2; l++){
                if(segment_intersects_segment_2d(points[0], m_outsidePoint, points2[l], points2[(l+1)%pointsCount2], NULL)){
                    interscount ++;
                }
            }
        }
        
        bool outer = (interscount % 2) == 0;
        
        TriangulatorPoly triangulator;
        for(int j = 0 ; j < pointsCount ; j++){
            triangulator[j] = points[j];
        }
        
        if(outer){
            triangulator.SetOrientation(TRIANGULATOR_CCW);
        }else{
            triangulator.SetOrientation(TRIANGULATOR_CW);
            triangulator.SetHole(true);
        }
        
        in_Triangulator.push_back(triangulator);
    }
    
    TriangulatorPartition tpart;
    if (tpart.ConvexPartition_HM(in_Triangulator, out_triangulator) == 0) {
        //failed!
        GSNavLog::getInstance().addErrorLog("ConvexPartition_HM fail");
        return;
    }
    m_polygons.clear();
    m_connections.clear();
    
    for(size_t i = 0 ; i < out_triangulator.size(); i++){
        TriangulatorPoly &tp = out_triangulator[i];
        
        GSPolygon p;
        
        for (int j = 0; j < tp.GetNumPoints(); j++) {
            p.points.push_back(tp[j]);
        }
        
        m_gspolygons.push_back(p);
    }
    
    m_polygons.resize(m_gspolygons.size());
    for(size_t gsPolygonIndex = 0 ; gsPolygonIndex < m_gspolygons.size(); gsPolygonIndex++){
        m_polygons.push_back(GSNavPolygon());
    }
    
    for(size_t gsPolygonIndex = 0 ; gsPolygonIndex < m_gspolygons.size(); gsPolygonIndex++){
        GSPolygon &gspolygon = m_gspolygons[gsPolygonIndex];
        
        std::vector<GSNavPoint> &points = gspolygon.points;
        int pointsCount = points.size();
        
        GSNavPolygon &polygon = m_polygons[gsPolygonIndex];
        polygon.center.x = 0;
        polygon.center.y = 0;
        
        polygon.edges.resize(pointsCount);
        
        for(int pointIndex = 0 ; pointIndex < pointsCount; pointIndex ++){
            GSNavEdge edge;
            GSNavPoint &point =points[pointIndex];
            edge.point = point;
            polygon.edges[pointIndex] = edge;
            
            polygon.center.x += point.x;
            polygon.center.y += point.y;
        }
        
        polygon.center.x /= pointsCount;
        polygon.center.y /= pointsCount;
        
        
        for(int pointIndex = 0 ; pointIndex < pointsCount; pointIndex ++){
            int nextIndex = (pointIndex+1) % pointsCount;
            
            GSNavEdgeKey edgeKey(polygon.edges[pointIndex].point,polygon.edges[nextIndex].point);
            
            std::vector<GSNavConnection>::iterator iter;
            for(iter = m_connections.begin(); iter != m_connections.end(); iter++){
                if(iter->edgeKey == edgeKey){
                    break;
                }
            }

            if(iter == m_connections.end()){
                GSNavConnection connection;
                connection.edgeKey = edgeKey;
                connection.A = &polygon;
                connection.A_edge = pointIndex;
                connection.B = NULL;
                connection.B_edge = -1;
                m_connections.push_back(connection);
            }else{
                GSNavConnection &connection = *iter;
                
                if(connection.B != NULL){
                    GSNavConnectionPending pending;
                    pending.polygon = &polygon;
                    pending.edge = pointIndex;
                    connection.pending.push_back(pending);
                    polygon.edges[pointIndex].P = &connection.pending;
                }else{
                    connection.B = &polygon;
                    connection.B_edge = pointIndex;
                    connection.A->edges[connection.A_edge].C = & polygon;
                    connection.A->edges[connection.A_edge].C_edge = pointIndex;
                    polygon.edges[pointIndex].C = connection.A;
                    polygon.edges[pointIndex].C_edge = connection.A_edge;
                }
            }
        }
    }
}

void GSNavMesh::adjustPoint(std::vector<GSNavPoint> &points)
{
    int pointsCount = points.size();
    if(m_navObstacles.size() == 1){
        m_outsidePoint.x = 0;
        m_outsidePoint.y = 0;
        m_outsidePointMin.x = INT_MAX;
        m_outsidePointMin.y = INT_MAX;
        //calculate outside
        for(int j = 0 ; j < pointsCount; j++){
            m_outsidePoint.x = std::max(m_outsidePoint.x, points[j].x );
            m_outsidePoint.y = std::max(m_outsidePoint.y, points[j].y );
            m_outsidePointMin.x = std::min(m_outsidePointMin.x, points[j].x );
            m_outsidePointMin.y = std::min(m_outsidePointMin.y, points[j].y );
        }
    }else{
        //clip outside
        for(int j = 0 ; j < pointsCount; j++){
            GSNavPoint &point = points[j];
            point.x = std::min(m_outsidePoint.x - 1, point.x);
            point.y = std::min(m_outsidePoint.y - 1, point.y);
            point.x = std::max(m_outsidePointMin.x + 1, point.x);
            point.y = std::max(m_outsidePointMin.y + 1, point.y);
        }
    }
}

GSStatus GSNavMesh::getClosestPoint(const GSNavPoint& findPoint,GSNavPoint& targetPoint,GSNavPolygon* targetPolygon)
{
    float min_d = 1e20;
    
    GSStatus status = GS_FAILURE;
    
    for(size_t i = 0 ; i < m_polygons.size(); i ++){
        GSNavPolygon &polygon = m_polygons[i];
        
        std::vector<GSNavEdge> &edges = polygon.edges;
        
        for(size_t edgeIndex = 0 ; edgeIndex < edges.size(); edgeIndex ++){
            
            GSNavPoint spoint = get_closest_point_to_segment_2d(findPoint, edges[edgeIndex].point, edges[(edgeIndex + 1)%edges.size()].point);
            
            float d = spoint.distance_to(findPoint);
            
            if(d < min_d){
                min_d = d;
                
                targetPolygon = &polygon;
                targetPoint = spoint;
                status = GS_SUCCESS;
            }
        }
    }
    
    return status;
}

GSStatus GSNavMesh::addObstacle(const std::vector<GSNavPoint>& points,GSID& id)
{
    this->m_state = GSNavMeshState::eNeedRefresh;
    
    GSNavObstacle obstacle;
    obstacle.id = next_obstacle_Id++;
    obstacle.alive = true;
    obstacle.polygon.points = points;
    m_navObstacles.push_back(obstacle);
    
    this->adjustPoint(m_navObstacles[m_navObstacles.size()-1].polygon.points);
    
    id = obstacle.id;
    
    return GS_SUCCESS;
}

GSStatus GSNavMesh::removeObstacle(const GSID id)
{
    for(int i = 0 ; i < m_navObstacles.size(); i ++){
        GSNavObstacle& obstacle = m_navObstacles[i];
        if(obstacle.id == id){
            
            m_navObstacles.erase(m_navObstacles.begin() + i);
    
            this->m_state = GSNavMeshState::eNeedRefresh;
            return GS_SUCCESS;
        }
    }
    
    return  GS_FAILURE;
}

GSStatus GSNavMesh::findPath(const GSNavPoint& start,const GSNavPoint &end,std::vector<GSNavPoint> &paths,bool optimize)
{
    GSNavPolygon* beginPolygon = NULL;
    GSNavPolygon* endPolygon = NULL;
    
    GSNavPoint beginPoint;
    GSNavPoint endPoint;
    
    float begin_d = 1e20;
    float end_d = 1e20;
    
    //look for point inside triangle
    for(size_t polygonIndex = 0 ; polygonIndex < m_polygons.size(); polygonIndex ++){
        GSNavPolygon &polygon = m_polygons[polygonIndex];
        
        if(begin_d || end_d){
            for(int i = 2; i < polygon.edges.size(); i++){
                if(begin_d > 0){
                    if(is_point_in_triangle(start, polygon.edges[0].point, polygon.edges[i-1].point, polygon.edges[i].point)){
                        beginPolygon = &polygon;
                        beginPoint = start;
                        begin_d = 0;
                        if(end_d == 0){
                            break;
                        }
                    }
                }
                
                if(end_d > 0){
                    if(is_point_in_triangle(end, polygon.edges[0].point, polygon.edges[i-1].point, polygon.edges[i].point)){
                        endPolygon = &polygon;
                        endPoint = end;
                        end_d = 0;
                        if(begin_d == 0){
                            break;
                        }
                    }
                }
            }
        }
        
        polygon.pre_edge = -1;
    }
    
    //start or end not inside triangle.. look for closest segment :|
    if(begin_d){
        if(getClosestPoint(start, beginPoint, beginPolygon)){
            begin_d = 0;
        }
    }
    
    if(end_d){
        if(getClosestPoint(end, endPoint, endPolygon)){
            end_d = 0;
        }
    }
    
    if(!beginPolygon || !endPolygon){
        return GS_FAILURE;
    }
    
    paths.clear();
    
    if(beginPolygon == endPolygon){
        paths.resize(2);
        paths[0] = endPoint;
        paths[1] = beginPoint;
        return GS_SUCCESS;
    }
    
    bool found_route = false;
    
    std::vector<GSNavPolygon*> openList;
    
    beginPolygon->entry = start;
    
    for(int i = 0 ; i < beginPolygon->edges.size();i++){
        GSNavEdge &edge = beginPolygon->edges[i];
        
        if(edge.C){
            edge.C->pre_edge = edge.C_edge;
            
            GSNavPoint entry = get_closest_point_to_segment_2d(beginPolygon->entry, beginPolygon->edges[i].point, beginPolygon->edges[(i+1)%beginPolygon->edges.size()].point);
            beginPolygon->edges[i].C->distance = beginPolygon->entry.distance_to(entry);
            beginPolygon->edges[i].C->entry = entry;
            
            openList.push_back(edge.C);
            
            if(edge.C == endPolygon){
                found_route = true;
            }
        }
    }
    
    while(!found_route){
        if(openList.size() == 0){
            break;
        }
        
        float least_cost = 1e30;
        GSNavPolygon *least_cost_polygon = NULL;
        
        for(size_t polygonIndex = 0 ; polygonIndex < openList.size(); polygonIndex ++){
            GSNavPolygon* polygon = openList[polygonIndex];
            float cost = polygon->distance;
            
            cost += polygon->center.distance_to(endPoint);
            
            if(cost < least_cost){
                least_cost = cost;
                least_cost_polygon = polygon;
            }
        }
        
        if(least_cost_polygon != NULL){
            for(size_t edgeIndex = 0 ; edgeIndex < least_cost_polygon->edges.size(); edgeIndex ++){
                GSNavEdge &edge = least_cost_polygon->edges[edgeIndex];
                
                if(!edge.C){
                    continue;
                }
                
                GSNavPoint edge_entry = get_closest_point_to_segment_2d(least_cost_polygon->entry, least_cost_polygon->edges[edgeIndex].point, least_cost_polygon->edges[(edgeIndex+1)%least_cost_polygon->edges.size()].point);
                float distance = least_cost_polygon->entry.distance_to(edge_entry) + least_cost_polygon->distance;
                
                
                if (edge.C->pre_edge != -1) {
                    //oh this was visited already, can we win the cost?
                    
                    if (edge.C->distance > distance) {
                        
                        edge.C->pre_edge = edge.C_edge;
                        edge.C->distance = distance;
                        edge.C->entry = edge_entry;
                    }
                } else {
                    //add to open neighbours
                    
                    edge.C->pre_edge = edge.C_edge;
                    edge.C->distance = distance;
                    edge.C->entry = edge_entry;
                    
                    openList.push_back(edge.C);
                    
                    if (edge.C == endPolygon) {
                        //oh my reached end! stop algorithm
                        found_route = true;
                        break;
                    }
                }
            }
            
            if(found_route){
                break;
            }
            
            std::vector<GSNavPolygon*>::iterator cost_polygon_itr = std::find(openList.begin(), openList.end(), least_cost_polygon);
            if(cost_polygon_itr != openList.end()){
                openList.erase(cost_polygon_itr);
            }
        }else{
            break;
        }
        
        
    }
    
    if(found_route == false){
        return GS_FAILURE;
    }
    
    if(optimize){
        
    }else{
        
    }
    
    GSNavPolygon *polygon = endPolygon;
    
    paths.push_back(endPoint);
    while (true) {
        
        GSNavPoint prep = polygon->edges[polygon->pre_edge].point;
        GSNavPoint prep_n = polygon->edges[(polygon->pre_edge + 1) % polygon->edges.size()].point;
        
        GSNavPoint point ((prep.x + prep_n.x) / 2, (prep_n.y + prep.y) / 2);
        paths.push_back(point);
        
        polygon = polygon->edges[polygon->pre_edge].C;
        if(polygon == beginPolygon){
            break;
        }
        
    }
    
    paths.push_back(beginPoint);
    
    return GS_SUCCESS;
}
