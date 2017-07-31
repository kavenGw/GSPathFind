//
//  GSPathFind.hpp
//  GSPathFind
//
//  Created by Can Wu on 2017/7/27.
//
//

#ifndef GSPathFind_hpp
#define GSPathFind_hpp

#include <stdio.h>
#include "GSNavData.hpp"
#include "GSNavCrowd.hpp"
#include "GSNavMesh.hpp"

class GSPathFind
{
private:
    GSNavMesh m_mesh;
    GSNavCrowd m_crowd;
public:
    GSPathFind();
    ~GSPathFind();
    
    //tick (ms)
    void update(int tick);
    
    void createNavMesh(const GSNavPolygon& polygon);
    
    GSStatus addObstacle(const GSNavPolygon& polygon,GSID& id);
    GSStatus removeObstacle(const GSID id);
    
    GSStatus findPath(const GSNavPoint& start,const GSNavPoint &end,std::vector<GSNavPoint> &paths,bool optimize = true);
    
    
    
};

#endif /* GSPathFind_hpp */
