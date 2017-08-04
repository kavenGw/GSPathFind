//
//  GSPathFind.hpp
//  GSPathFind
//
//  Created by Can Wu on 2017/7/27.
//
//

#ifndef GSPathFind_hpp
#define GSPathFind_hpp

#include <stdio.h>
#include "GSNavData.hpp"
#include "GSNavCrowd.hpp"
#include "GSNavMesh.hpp"

class GSPathFind
{
private:
    GSNavMesh m_mesh;
    GSNavCrowd m_crowd;
public:
    GSPathFind();
    ~GSPathFind();
    
    //tick (ms)
    void update(int tick);
    
    void createNavMesh(const GSPolygon& polygon);
    
    GSStatus addObstacle(const std::vector<GSNavPoint>& points,GSID& id);
    GSStatus addObstacle(const int midx,const int midy,const int w,const int h,GSID& id);
    GSStatus removeObstacle(const GSID id);
    
    GSStatus addAgent(const GSNavPoint& point,const GSNavAgentParams& param,GSID &idx);
    GSStatus removeAgent(GSID &idx);
    GSStatus moveAgent(const GSID& idx,const GSNavPoint& targetPoint);
    GSStatus stop(const GSID& id);
    GSStatus changeAgentSpeed(const GSID& id,const int newSpeedx,const int newSpeedy);
    
    inline GSNavMesh* getNavMesh(){return &m_mesh;}
    inline GSNavCrowd* getCrowd(){return &m_crowd;}
    
    GSNavAgent* getAgents()
    {
        return m_crowd.m_agents;
    };
    int getMaxAgents(){
        return m_crowd.m_maxAgents;
    };
    
};

#endif /* GSPathFind_hpp */
