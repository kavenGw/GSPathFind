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
    m_crowd.init(&m_mesh, 200);
}

GSPathFind::~GSPathFind()
{

}

void GSPathFind::update(int tick)
{
    m_mesh.update(tick);
    m_crowd.update(tick);
}

void GSPathFind::createNavMesh(const GSPolygon& polygon)
{
    m_mesh.init(polygon);
}

GSStatus GSPathFind::addObstacle(const std::vector<GSNavPoint>& points,GSID& id)
{
    return m_mesh.addObstacle(points, id);
}

GSState GSPathFind::addObstacle(const int midx,const int midy,const int w,const int h,GSID& id)
{
    if(w == 0 || h == 0){
        return GS_FAILURE;
    }
    
    std::vector<GSNavPoint> points;
    points.push_back(GSNavPoint(midx - w / 2,midy - h / 2));
    points.push_back(GSNavPoint(midx + w / 2,midy - h / 2));
    points.push_back(GSNavPoint(midx + w / 2,midy + h / 2));
    points.push_back(GSNavPoint(midx - w / 2,midy + h / 2));
    return addObstacle(points, id);
}

GSStatus GSPathFind::removeObstacle(const GSID id)
{
    return m_mesh.removeObstacle(id);
}

GSStatus GSPathFind::addAgent(const GSNavPoint& point,const GSNavAgentParams& param,GSID &idx)
{
    return m_crowd.addAgent(point,param,idx);
}

GSStatus GSPathFind::removeAgent(GSID &idx)
{
    return m_crowd.removeAgent(idx);
}

GSStatus GSPathFind::stop(const GSID& idx)
{
    return m_crowd.stop(idx);
}

GSStatus GSPathFind::changeAgentSpeed(const GSID& idx,const int newSpeedx,const int newSpeedy)
{
    return m_crowd.changeAgentSpeed(idx,newSpeedx,newSpeedy);
}

GSStatus GSPathFind::moveAgent(const GSID& idx,const GSNavPoint& targetPoint)
{
    return m_crowd.moveAgent(idx,targetPoint);
}
