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
static const unsigned int GS_FAILURE = 1u << 31;			// Operation failed.
static const unsigned int GS_SUCCESS = 1u << 30;			// Operation succeed.

typedef int GSID;

class GSNavPoint
{
public:
    int x;
    int y;
    
    GSNavPoint(const int vx = 0,const int vy = 0);
};

class GSNavLine
{
public:
    GSNavPoint a;
    GSNavPoint b;
    
    GSNavLine(const GSNavPoint &p_a = GSNavPoint(),const GSNavPoint &p_b = GSNavPoint());

    int width();
    int height();
};

class GSNavEdge
{
public:
    GSNavPoint a;
    GSNavPoint b;
    
    GSNavEdge(const GSNavPoint &p_a = GSNavPoint(),const GSNavPoint &p_b = GSNavPoint());
};

class GSNavPolygon
{
public:
    GSNavPolygon();
};

class GSNavConnectionPending
{
public:
    GSNavPolygon* polygon;
    
    GSNavConnectionPending();
};

class GSNavConnection
{
public:
    GSNavConnection();
};

class GSNavMesh
{
public:
    GSNavMesh();
};

#endif /* GSNavData_hpp */
