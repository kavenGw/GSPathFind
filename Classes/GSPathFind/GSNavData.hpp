//
//  GSNavData.hpp
//  GSPathFind
//
//  Created by Can Wu on 2017/7/27.
//
//

#ifndef GSNavData_hpp
#define GSNavData_hpp

#include <stdio.h>

typedef unsigned int GSStatus;
// High level status.
static const GSStatus GS_FAILURE = 1u << 31;			// Operation failed.
static const GSStatus GS_SUCCESS = 1u << 30;			// Operation succeed.

typedef unsigned int GSState;
static const GSState GSState_none = 0;
static const GSState GSState_add = 1;
static const GSState GSState_remove = 2;
static const GSState GSState_start_move = 3;
static const GSState GSState_stop_move = 4;
static const GSState GSState_moving = 5;

#define SWAP(m_x, m_y) __swap_tmpl(m_x, m_y)
template <class T>
inline void __swap_tmpl(T &x, T &y) {
    
    T aux = x;
    x = y;
    y = aux;
}

typedef int GSID;

class GSNavPoint
{
public:
    struct {
        int x ;
        int y ;
    };
    
    int distance_to(const GSNavPoint &p_GSNavPoint) const;
    int distance_squared_to(const GSNavPoint &p_GSNavPoint) const;
    int dot(const GSNavPoint &p_other) const;
    int length() const;
    
    GSNavPoint operator+(const GSNavPoint &p_v) const;
    void operator+=(const GSNavPoint &p_v);
    GSNavPoint operator-(const GSNavPoint &p_v) const;
    void operator-=(const GSNavPoint &p_v);
    GSNavPoint operator*(const GSNavPoint &p_v1) const;
    GSNavPoint operator*(const int &rvalue) const;
    void operator*=(const int &rvalue);
    void operator*=(const GSNavPoint &rvalue) { *this = *this * rvalue; }
    GSNavPoint operator/(const GSNavPoint &p_v1) const;
    GSNavPoint operator/(const int &rvalue) const;
    void operator/=(const int &rvalue);
    GSNavPoint operator-() const;
    
    bool operator==(const GSNavPoint &p_vec2) const;
    bool operator!=(const GSNavPoint &p_vec2) const;
    
    bool operator<(const GSNavPoint &p_vec2) const { return (x == p_vec2.x) ? (y < p_vec2.y) : (x < p_vec2.x); }
    bool operator<=(const GSNavPoint &p_vec2) const { return (x == p_vec2.x) ? (y <= p_vec2.y) : (x <= p_vec2.x); }
    
    GSNavPoint(int x = 0,int y = 0);
};

class GSNavEdgeKey
{
public:
    GSNavPoint a;
    GSNavPoint b;
    bool operator<(const GSNavEdgeKey &p_key) const {
        return (a == p_key.a) ? (b < p_key.b) : (a < p_key.a);
    };
    GSNavEdgeKey(const GSNavPoint &p_a = GSNavPoint(), const GSNavPoint &p_b = GSNavPoint());
};

class GSNavPolygon;

class GSNavConnectionPending
{
public:
    GSNavPolygon* polygon;
    int edge;
    
    GSNavConnectionPending();
};

class GSNavEdge
{
public:
    GSNavPoint point;
    GSNavPolygon *C;//connection
    int C_edge;
    std::vector<GSNavConnectionPending> *P;
    
    GSNavEdge();
};

class GSNavPolygon
{
public:
    GSNavPolygon();
    
    std::vector<GSNavEdge> edges;

    GSNavPoint center;
    GSNavPoint entry;
    
    float distance;
    int pre_edge;
};

class GSNavRect : public GSNavPolygon
{
public:
    GSNavRect();
    void init(const int v_xmin,const int v_ymin,const int v_w,const int v_h);
    void init(const GSNavPoint& point,const int v_w,const int v_h);
    void refreshPoints();

    int x_min;
    int y_min;
    int x_max;
    int y_max;
    int x_mid;
    int y_mid;
    int w;
    int h;
};

class GSNavConnection
{
public:
    GSNavPolygon *A;
    int A_edge;
    GSNavPolygon *B;
    int B_edge;
    
    std::vector<GSNavConnectionPending> pending;
    
    GSNavConnection();
};

class GSNavObstacle
{
public:
    std::vector<GSNavPoint> points;
    GSID id;
};

#endif /* GSNavData_hpp */
