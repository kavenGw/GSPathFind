//
//  GSPathFind.cpp
//  GSPathFind
//
//  Created by Can Wu on 2017/7/27.
//
//

#include "GSPathFind.hpp"

GSPathFind::GSPathFind()
{
    
}

GSPathFind::~GSPathFind()
{

}

void GSPathFind::update(int tick)
{

}

void GSPathFind::createNavMesh(const int width,const int height)
{

}


GSNavPoint GSPathFind::getClosestPoint(const GSNavPoint& point)
{

}

GSStatus GSPathFind::addObstacle(const GSNavPolygon& polygon,GSID& id)
{
    return GS_SUCCESS;
}

GSStatus GSPathFind::removeObstacle(const GSID id)
{
    return GS_SUCCESS;
}

GSStatus GSPathFind::findPath(const GSNavPoint& start,const GSNavPoint &end,bool optimize)
{
    return GS_SUCCESS;
}

void GSPathFind::move(GSNavPoint &nowPos, const GSNavPoint &start, const GSNavPoint &end, int speed)
{
    
}
