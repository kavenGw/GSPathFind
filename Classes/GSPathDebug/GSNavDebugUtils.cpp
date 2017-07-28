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

void debugGSNavLine(const GSNavLine& line)
{
    printf("line----");
    debugGSNavPoint(line.a);
    debugGSNavPoint(line.b);
    printf("w:%d h:%d",line.width(),line.height());
    printf("--------");
}

void debugGSNavEdge(const GSNavEdge& edge)
{
    
}

void debugGSNavPolygon(const GSNavPolygon& polygon)
{
    printf("debugGSNavPolygon---");
    for (size_t i = 0; i < polygon.points.size(); i++) {
        debugGSNavPoint(polygon.points[i]);
    }
    printf("--------------------");
}

void debugGSNavRect(const GSNavRect& rect)
{
    printf("debugGSNavRect--------");
    debugGSNavPolygon(rect);
    printf("xmin:%d ymin:%d xmid:%d ymid:%d xmax:%d ymax:%d w:%d h:%d",rect.x_min,rect.y_min,rect.x_mid,rect.y_mid,rect.x_max,rect.y_max,rect.w,rect.h);
    printf("----------------------");
}
