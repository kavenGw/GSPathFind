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

bool _move(int &pos, const int &target, const int &v, const int &t)
{
    int dis = target - pos;
    int disABS = std::abs(dis);
    
    if(dis == 0){
        return true;
    }
    
    int move = v * t * disABS / dis;
    if(disABS < std::abs(move))
    {
        pos = target;
        return true;
    }else{
        pos = pos + move;
    }
    
    return false;
}

bool move(GSNavPoint &nowPos, const GSNavPoint &start, const GSNavPoint &end, const int speed,const int t)
{
    bool resultx = _move(nowPos.x, end.x, speed, t);
    bool resulty = _move(nowPos.y, end.y, speed, t);
    
    return resultx && resulty;
}
