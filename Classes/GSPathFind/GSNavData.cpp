//
//  GSNavData.cpp
//  GSPathFind
//
//  Created by Can Wu on 2017/7/27.
//
//

#include "GSNavData.hpp"

///GSNavPoint
GSNavPoint::GSNavPoint(int v_x,int v_y)
{
    this->x = v_x;
    this->y = v_y;
}

int GSNavPoint::distance_to(const GSNavPoint &p_GSNavPoint) const {
    
    return sqrt((x - p_GSNavPoint.x) * (x - p_GSNavPoint.x) + (y - p_GSNavPoint.y) * (y - p_GSNavPoint.y));
}

int GSNavPoint::distance_squared_to(const GSNavPoint &p_GSNavPoint) const {
    
    return (x - p_GSNavPoint.x) * (x - p_GSNavPoint.x) + (y - p_GSNavPoint.y) * (y - p_GSNavPoint.y);
}

int GSNavPoint::dot(const GSNavPoint &p_other) const {
    
    return x * p_other.x + y * p_other.y;
}

int GSNavPoint::length() const
{
    return sqrt(x * x + y * y);
}

//bug
GSNavPoint GSNavPoint::Normalize()
{
    GSNavPoint r(this->x,this->y);
    int n = length();
    if(n!=0) {
        r.x = r.x / n;
        r.y = r.y / n;
    } else {
        r.x = 0;
        r.y = 0;
    }
    return r;
}

GSNavPoint GSNavPoint::operator+(const GSNavPoint &p_v) const {
    
    return GSNavPoint(x + p_v.x, y + p_v.y);
}
void GSNavPoint::operator+=(const GSNavPoint &p_v) {
    
    x += p_v.x;
    y += p_v.y;
}
GSNavPoint GSNavPoint::operator-(const GSNavPoint &p_v) const {
    
    return GSNavPoint(x - p_v.x, y - p_v.y);
}
void GSNavPoint::operator-=(const GSNavPoint &p_v) {
    
    x -= p_v.x;
    y -= p_v.y;
}

GSNavPoint GSNavPoint::operator*(const GSNavPoint &p_v1) const {
    
    return GSNavPoint(x * p_v1.x, y * p_v1.y);
};

GSNavPoint GSNavPoint::operator*(const int &rvalue) const {
    
    return GSNavPoint(x * rvalue, y * rvalue);
};
void GSNavPoint::operator*=(const int &rvalue) {
    
    x *= rvalue;
    y *= rvalue;
};

GSNavPoint GSNavPoint::operator/(const GSNavPoint &p_v1) const {
    
    return GSNavPoint(x / p_v1.x, y / p_v1.y);
};

GSNavPoint GSNavPoint::operator/(const int &rvalue) const {
    
    return GSNavPoint(x / rvalue, y / rvalue);
};

void GSNavPoint::operator/=(const int &rvalue) {
    
    x /= rvalue;
    y /= rvalue;
};

GSNavPoint GSNavPoint::operator-() const {
    
    return GSNavPoint(-x, -y);
}

bool GSNavPoint::operator==(const GSNavPoint &p_vec2) const {
    
    return x == p_vec2.x && y == p_vec2.y;
}
bool GSNavPoint::operator!=(const GSNavPoint &p_vec2) const {
    
    return x != p_vec2.x || y != p_vec2.y;
}

//GSNavEdgeKey
GSNavEdgeKey::GSNavEdgeKey(const GSNavPoint &p_a, const GSNavPoint &p_b)
{
    a = p_a;
    b = p_b;
}

///GSNavConnectionPending
GSNavConnectionPending::GSNavConnectionPending()
{
    
}

///GSNavEdge
GSNavEdge::GSNavEdge()
{
    C = NULL;
    C_edge = -1;
    P = NULL;
}

///GSNavPolygon
GSNavPolygon::GSNavPolygon()
{

}

///GSNavConnection
GSNavConnection::GSNavConnection()
{
    A = NULL;
    B = NULL;
    A_edge = -1;
    B_edge = -1;
}
