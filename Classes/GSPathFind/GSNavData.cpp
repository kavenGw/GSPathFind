//
//  GSNavData.cpp
//  GSPathFind
//
//  Created by Can Wu on 2017/7/27.
//
//

#include "GSNavData.hpp"

///GSNavPoint
GSNavPoint::GSNavPoint(const int vx ,const int vy )
{
    this->x = vx;
    this->y = vy;
}

///GSNavLine
GSNavLine::GSNavLine(const GSNavPoint &p_a ,const GSNavPoint &p_b)
{
    this->a = p_a;
    this->b = p_b;
}

int GSNavLine::width()
{
    return abs(a.x - b.x);
}

int GSNavLine::height()
{
    return abs(a.y - b.y);
}

///GSNavEdge
GSNavEdge::GSNavEdge(const GSNavPoint &p_a ,const GSNavPoint &p_b)
{
    this->a = p_a;
    this->b = p_b;
}

///GSNavPolygon
GSNavPolygon::GSNavPolygon()
{

}

///GSNavConnectionPending
GSNavConnectionPending::GSNavConnectionPending()
{

}

///GSNavConnection
GSNavConnection::GSNavConnection()
{

}

///GSNavMesh
GSNavMesh::GSNavMesh()
{

}
