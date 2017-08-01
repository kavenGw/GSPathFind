//
//  GSNavMath.cpp
//  GSPathFind
//
//  Created by Can Wu on 2017/7/31.
//
//

#include "GSNavMath.hpp"

bool is_point_in_triangle(const GSNavPoint &s, const GSNavPoint &a, const GSNavPoint &b, const GSNavPoint &c)
{
    int as_x = s.x - a.x;
    int as_y = s.y - a.y;
    
    bool s_ab = (b.x - a.x) * as_y - (b.y - a.y) * as_x > 0;
    
    if (((c.x - a.x) * as_y - (c.y - a.y) * as_x > 0) == s_ab) return false;
    
    if (((c.x - b.x) * (s.y - b.y) - (c.y - b.y) * (s.x - b.x) > 0) != s_ab) return false;
    
    return true;
}



GSNavPoint get_closest_point_to_segment_2d(const GSNavPoint &p_point, const GSNavPoint &point1,const GSNavPoint&point2)
{
    GSNavPoint p = p_point - point1;
    GSNavPoint n = point2 - point1;
    int l = n.length();
    if (l < 1e-10)
        return point1; // both points are the same, just give any
    n /= l;
    
    int d = n.dot(p);
    
    if (d <= 0.0)
        return point1; // before first point
    else if (d >= l)
        return point2; // after first point
    else
        return point1 + n * d; // inside
}



void gsFormatpos(int x, int& x2)
{
    if(x < 0.0f)
    {
        x2 = 0;
    }
    else
    {
        x2 = x;
    }
}

bool gsMove(GSNavPoint &nowPos, const GSNavPoint &end, const int speed)
{
    
    int dx = end.x - nowPos.x;
    int dy = end.y - nowPos.y;
    
    int d = dx*dx + dy*dy;
    float speed_square = speed * speed;
    
    if(speed_square >= d)
    {
        nowPos = end;
        return true;
    }
    
    int sloop = sqrt(d);
    gsFormatpos(nowPos.x + (dx*speed/sloop), nowPos.x);
    gsFormatpos(nowPos.y + (dy*speed/sloop), nowPos.y);
    
    return false;
}
