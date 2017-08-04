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
#include <stdlib.h>
#include <vector>

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
static const int GSNavPrecision = 1000;

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
    GSNavPoint Normalize();
    
    GSNavPoint operator+(const GSNavPoint &p_v) const;
    void operator+=(const GSNavPoint &p_v);
    GSNavPoint operator-(const GSNavPoint &p_v) const;
    void operator-=(const GSNavPoint &p_v);
    GSNavPoint operator*(const GSNavPoint &p_v1) const;
    GSNavPoint operator*(const int &rvalue) const;
    void operator*=(const int &rvalue);
    void operator*=(const GSNavPoint &rvalue) { *this = *this * rvalue; }
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
    bool operator==(const GSNavEdgeKey &p_key) const;
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

class GSPolygon{
public:
    std::vector<GSNavPoint> points;
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
    
    GSNavEdgeKey edgeKey;
};

class GSNavObstacle
{
public:
    GSPolygon polygon;
    GSID id;
    bool alive;
};

#endif /* GSNavData_hpp */
