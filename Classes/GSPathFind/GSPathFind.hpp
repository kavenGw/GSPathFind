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

class GSPathFind
{
private:
    
public:
    GSPathFind();
    ~GSPathFind();
    
    //tick (ms)
    void update(int tick);
    
    void createNavMesh(const int width,const int height);
    
    GSNavPoint getClosestPoint(const GSNavPoint& point);
    
    GSStatus addObstacle(const GSNavPolygon& polygon,GSID& id);
    GSStatus removeObstacle(const GSID id);
    
    GSStatus findPath(const GSNavPoint& start,const GSNavPoint &end,bool optimize = true);
    
    void move(GSNavPoint& nowPos,const GSNavPoint& start,const GSNavPoint &end,int speed);
};

#endif /* GSPathFind_hpp */
