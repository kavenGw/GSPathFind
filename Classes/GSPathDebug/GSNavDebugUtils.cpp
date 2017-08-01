//
//  GSNavDebugUtils.cpp
//  GSPathFind
//
//  Created by Can Wu on 2017/7/28.
//
//

#include "GSNavDebugUtils.hpp"

void debugGSNavPoint(const GSNavPoint& point)
{
    printf("x:%d y:%d ",point.x,point.y);
}

void debugGSNavEdge(const GSNavEdge& edge)
{
    
}

void debugGSNavPolygon(const GSNavPolygon& polygon)
{
    printf("debugGSNavPolygon---");
    for (size_t i = 0; i < polygon.edges.size(); i++) {
        debugGSNavPoint(polygon.edges[i].point);
    }
    printf("--------------------");
}
