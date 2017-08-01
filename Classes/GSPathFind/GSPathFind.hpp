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
    
    void createNavMesh(const GSPolygon& polygon);
    
    GSStatus addObstacle(const std::vector<GSNavPoint>& points,GSID& id);
    GSStatus addObstacle(const int midx,const int midy,const int w,const int h,GSID& id);
    GSStatus removeObstacle(const GSID id);
    
    GSStatus findPath(const GSNavPoint& start,const GSNavPoint &end,std::vector<GSNavPoint> &paths,bool optimize = true);
    
    inline GSNavMesh* getNameMesh(){return &m_mesh;}
    
};

#endif /* GSPathFind_hpp */
