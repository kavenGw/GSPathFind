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

///GSNavMesh
GSNavMesh::GSNavMesh()
{
    
}

GSNavMesh::~GSNavMesh()
{
    
}

void GSNavMesh::init(const GSNavPolygon &polygon)
{
    m_navObstacles.clear();
    m_vertices.clear();
    m_connections.clear();
    
    this->m_polygon = polygon;
    
    this->m_state = GSNavMeshState::eNormal;
}


void GSNavMesh::update(int dt)
{
    if(this->m_state == GSNavMeshState::eNormal){
        return;
    }
    
    std::vector<GSNavObstacle> &obstacles = m_navObstacles;
    
    for(size_t obstacleIndex = 0 ; obstacleIndex < obstacles.size(); obstacleIndex++){
        GSNavObstacle &obstacle = obstacles[obstacleIndex];
        
        std::vector<GSNavPoint> &points = obstacle.points;
        int pointsCount = points.size();
        
        GSNavPolygon polygon;
        polygon.center.x = 0;
        polygon.center.y = 0;
        m_polygons.push_back(polygon);
        
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
            
            const std::map<GSNavEdgeKey, GSNavConnection>::iterator iter = m_connections.find(edgeKey);

            if(iter == m_connections.end()){
                GSNavConnection connection;
                connection.A = &polygon;
                connection.A_edge = pointIndex;
                connection.B = NULL;
                connection.B_edge = -1;
                m_connections[edgeKey] = connection;
            }else{
                GSNavConnection &connection = iter->second;
                
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
    
    this->m_state = GSNavMeshState::eNormal;
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

GSStatus GSNavMesh::addObstacle(const GSNavPolygon& polygon,GSID& id)
{
    this->m_state = GSNavMeshState::eNeedRefresh;
    return GS_SUCCESS;
}

GSStatus GSNavMesh::removeObstacle(const GSID id)
{
    this->m_state = GSNavMeshState::eNeedRefresh;
    return GS_SUCCESS;
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
        paths[0] = beginPoint;
        paths[1] = endPoint;
        return GS_SUCCESS;
    }
    
    bool found_route = false;
    
    std::vector<GSNavPolygon*> openList;
    
    beginPolygon->entry = start;
    
    for(int i = 0 ; i < beginPolygon->edges.size();i++){
        GSNavEdge &edge = beginPolygon->edges[i];
        
        if(edge.C){
            edge.C->pre_edge = edge.C_edge;
            edge.C->distance = beginPolygon->center.distance_to(edge.C->center);
        }
        
        openList.push_back(edge.C);
    
        if(edge.C == endPolygon){
            found_route = true;
        }
    }
    
    while(!found_route){
        if(openList.size() == 0){
            break;
        }
        
        float least_cost = 1e30;
        GSNavPolygon *least_cost_polygon = NULL;
        
        for(size_t polygonIndex = 0 ; polygonIndex < m_polygons.size(); polygonIndex ++){
            GSNavPolygon &polygon = m_polygons[polygonIndex];
            
            float cost = polygon.distance;
            
            cost += polygon.center.distance_to(endPoint);
            
            if(cost < least_cost){
                least_cost = cost;
                least_cost_polygon = &polygon;
            }
        }
        
        if(least_cost_polygon != NULL){
            for(size_t edgeIndex = 0 ; edgeIndex < least_cost_polygon->edges.size(); edgeIndex ++){
                GSNavEdge &edge = least_cost_polygon->edges[edgeIndex];
                
                if(!edge.C){
                    continue;
                }
                
                float distance = least_cost_polygon->center.distance_to(edge.C->center) + least_cost_polygon->distance;
                
                
                if (edge.C->pre_edge != -1) {
                    //oh this was visited already, can we win the cost?
                    
                    if (edge.C->distance > distance) {
                        
                        edge.C->pre_edge = edge.C_edge;
                        edge.C->distance = distance;
                    }
                } else {
                    //add to open neighbours
                    
                    edge.C->pre_edge = edge.C_edge;
                    edge.C->distance = distance;
                    
                    openList.push_back(edge.C);
                    
                    if (edge.C == endPolygon) {
                        //oh my reached end! stop algorithm
                        found_route = true;
                        break;
                    }
                }
            }
        }
        
        if(found_route){
            break;
        }
        
        if(least_cost_polygon!= NULL){
            openList.erase(std::find(openList.begin(), openList.end(), least_cost_polygon));
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
        int prev = polygon->pre_edge;
        int prev_n = (prev + 1) & polygon->edges.size();
        
        GSNavPoint point = (polygon->edges[prev].point + polygon->edges[prev_n].point) * 50 / 100;
        paths.push_back(point);
        
        polygon = polygon->edges[prev].C;
        if(polygon == beginPolygon){
            break;
        }
    }
    
    paths.push_back(beginPoint);
    
    return GS_SUCCESS;
}
