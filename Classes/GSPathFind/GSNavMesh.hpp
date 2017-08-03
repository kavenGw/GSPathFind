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
public:
    GSNavMesh();
    ~GSNavMesh();
    
    void init(const GSPolygon& polygon);
    void reset();
    //dt (ms)
    void update(int dt);
    
    GSStatus getClosestPoint(const GSNavPoint& point,GSNavPoint& targetPoint,GSNavPolygon* polygon);
    GSStatus addObstacle(const std::vector<GSNavPoint>& points,GSID& id);
    GSStatus removeObstacle(const GSID id);
    GSStatus findPath(const GSNavPoint& start,const GSNavPoint &end,std::vector<GSNavPoint> &paths,bool optimize = true);
    
    std::vector<GSNavObstacle> m_navObstacles;
    std::vector<GSPolygon> m_gspolygons;
    std::vector<GSNavPolygon> m_polygons;
    std::vector<GSNavConnection> m_connections;
    
    GSID next_obstacle_Id;
    
    GSNavMeshState m_state;
};

#endif /* GSNavMesh_hpp */
