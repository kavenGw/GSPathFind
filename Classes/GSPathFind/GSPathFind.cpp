//
//  GSPathFind.cpp
//  GSPathFind
//
//  Created by Can Wu on 2017/7/27.
//
//

#include "GSPathFind.hpp"

GSPathFind::GSPathFind()
{
    
}

GSPathFind::~GSPathFind()
{

}

void GSPathFind::update(int tick)
{
    m_mesh.update(tick);
    m_crowd.update(tick);
}

void GSPathFind::createNavMesh(const GSNavPolygon& polygon)
{
    m_mesh.init(polygon);
}

GSStatus GSPathFind::addObstacle(const GSNavPolygon& polygon,GSID& id)
{
    return m_mesh.addObstacle(polygon, id);
}

GSStatus GSPathFind::removeObstacle(const GSID id)
{
    return m_mesh.removeObstacle(id);
}

GSStatus GSPathFind::findPath(const GSNavPoint& start,const GSNavPoint &end,std::vector<GSNavPoint> &paths,bool optimize)
{
    return m_mesh.findPath(start, end, paths, optimize);
}
