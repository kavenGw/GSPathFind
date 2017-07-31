//
//  GSNavMesh.hpp
//  GSPathFind
//
//  Created by Can Wu on 2017/7/28.
//
//

#ifndef GSNavMesh_hpp
#define GSNavMesh_hpp

#include <stdio.h>
#include "GSNavData.hpp"

enum GSNavMeshState
{
    eNormal,
    eNeedRefresh,
};

class GSNavMesh
{
private:
    GSNavPolygon m_polygon;
public:
    GSNavMesh();
    ~GSNavMesh();
    
    void init(const GSNavPolygon& polygon);
    //dt (ms)
    void update(int dt);
    
    GSStatus getClosestPoint(const GSNavPoint& point,GSNavPoint& targetPoint,GSNavPolygon* polygon);
    GSStatus addObstacle(const GSNavPolygon& polygon,GSID& id);
    GSStatus removeObstacle(const GSID id);
    GSStatus findPath(const GSNavPoint& start,const GSNavPoint &end,std::vector<GSNavPoint> &paths,bool optimize = true);
    
    
private:
    std::vector<GSNavObstacle> m_navObstacles;
    std::vector<GSNavPoint> m_vertices;
    std::vector<GSNavPolygon> m_polygons;
    
    std::map<GSNavEdgeKey, GSNavConnection> m_connections;
    
    GSNavMeshState m_state;
};

#endif /* GSNavMesh_hpp */
