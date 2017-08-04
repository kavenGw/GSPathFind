//
//  GSNavMath.cpp
//  GSPathFind
//
//  Created by Can Wu on 2017/7/31.
//
//

#include "GSNavMath.hpp"
#include <math.h>

bool is_point_in_triangle(const GSNavPoint &s, const GSNavPoint &a, const GSNavPoint &b, const GSNavPoint &c)
{
    int as_x = s.x - a.x;
    int as_y = s.y - a.y;
    
    bool s_ab = (b.x - a.x) * as_y - (b.y - a.y) * as_x > 0;
    
    if (((c.x - a.x) * as_y - (c.y - a.y) * as_x > 0) == s_ab) return false;
    
    if (((c.x - b.x) * (s.y - b.y) - (c.y - b.y) * (s.x - b.x) > 0) != s_ab) return false;
    
    return true;
}



bool segment_intersects_segment_2d(const GSNavPoint &p_from_a, const GSNavPoint &p_to_a, const GSNavPoint &p_from_b, const GSNavPoint &p_to_b, GSNavPoint *r_result)
{
    
    GSNavPoint B = p_to_a - p_from_a;
    GSNavPoint C = p_from_b - p_from_a;
    GSNavPoint D = p_to_b - p_from_a;
    
    int ABlen = B.dot(B);
    if (ABlen <= 0)
        return false;
//    GSNavPoint Bn = B / ABlen;
    GSNavPoint Bn(B.x * GSNavPrecision / ABlen,B.y * GSNavPrecision / ABlen);
    C = GSNavPoint(C.x * Bn.x + C.y * Bn.y, C.y * Bn.x - C.x * Bn.y);
    D = GSNavPoint(D.x * Bn.x + D.y * Bn.y, D.y * Bn.x - D.x * Bn.y);
    
    if ((C.y < 0 && D.y < 0) || (C.y >= 0 && D.y >= 0))
        return false;
    
    int ABpos = D.x + (C.x - D.x) * D.y / (D.y - C.y);
    
    //  Fail if segment C-D crosses line A-B outside of segment A-B.
    if (ABpos < 0 || ABpos > 1 * GSNavPrecision )
        return false;
    
    //  (4) Apply the discovered position to line A-B in the original coordinate system.
    if (r_result)
        *r_result = p_from_a + GSNavPoint(B.x * ABpos / GSNavPrecision, B.y * ABpos / GSNavPrecision);
    
    return true;
}


GSNavPoint get_closest_point_to_segment_2d(const GSNavPoint &p_point, const GSNavPoint &point1,const GSNavPoint&point2)
{
    GSNavPoint p = p_point - point1;
    GSNavPoint n = point2 - point1;
    int l = n.length();
    if (l == 0)
        return point1; // both points are the same, just give any
    n = GSNavPoint(n.x * GSNavPrecision / l,n.y * GSNavPrecision / l);

    int d = n.dot(p);
    
    if (d <= 0)
        return point1; // before first point
    else if (d >= l * GSNavPrecision)
        return point2; // after first point
    else
        return point1 + GSNavPoint(n.x * d / GSNavPrecision,n.y * d / GSNavPrecision); // inside
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

bool gsMove(GSNavPoint& nowPos,const GSNavPoint &end,int& leftSpeed,GSNavPoint& leftPos, const GSNavPoint& const_speed,const int tick)
{
    if(const_speed.x == 0){
        leftSpeed = 0;
        nowPos = end;
        return true;
    }
    
    leftSpeed += const_speed.y * tick;
    
    int speed = leftSpeed / 1000;
    
    int dx = (end.x - nowPos.x) * const_speed.y / const_speed.x;
    int dy = end.y - nowPos.y;
    
    int d = dx*dx + dy*dy;
    float speed_square = speed * speed;
    
    if(speed_square >= d)
    {
        leftSpeed = 0;
        nowPos = end;
        return true;
    }
    leftSpeed = leftSpeed - speed * 1000;
    
    leftPos += GSNavPoint(dx*speed*const_speed.x/const_speed.y,dy*speed);
    
    int sloop = sqrt(d);
    
    if(abs(leftPos.x) >= sloop){
        gsFormatpos(nowPos.x + (leftPos.x/sloop), nowPos.x);
        leftPos.x = leftPos.x % sloop;
    }
    
    if(abs(leftPos.y) >= sloop){
        gsFormatpos(nowPos.y + (leftPos.y/sloop), nowPos.y);
        leftPos.y = leftPos.y % sloop;
    }
    
    
    return false;
}
