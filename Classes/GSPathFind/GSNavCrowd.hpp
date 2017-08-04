//
//  GSCrowed.hpp
//  GSPathFind
//
//  Created by Can Wu on 2017/7/27.
//
//

#ifndef GSNavCrowd_hpp
#define GSNavCrowd_hpp

#include <stdio.h>
#include "GSNavData.hpp"
#include "GSNavMesh.hpp"

class GSNavAgentParams
{
public:
    int w;
    int h;
    GSNavPoint m_speed;

    GSNavAgentParams();
};

enum GSNavAgentState
{
    eNone,
    eFindTarget,
    eMoving,
    eFinishMove,
};

class GSNavAgent
{
public:
    bool m_active;
    GSID m_id;
    GSNavPoint m_pos;
    GSNavPoint m_targetPos;
    
    int m_leftSpeed;
    GSNavPoint m_leftPos;
    
    std::vector<GSNavPoint> m_paths;
    
    GSNavAgentParams m_param;
    GSNavAgentState m_state;
    
    GSNavAgent();
    ~GSNavAgent();
    
    GSNavPoint getNextTargetPoint();
};

class GSNavCrowd
{
private:
    GSNavMesh* m_mesh;
public:
    GSNavCrowd();
    ~GSNavCrowd();
    
    GSStatus init(GSNavMesh* mesh,const int maxAgent);
    void update(const int tick);
    
    GSNavAgent* getNavAgent(const GSID& idx);
    GSStatus addAgent(const GSNavPoint& point,const GSNavAgentParams& param,GSID &idx);
    GSStatus removeAgent(const GSID& idx);
    GSStatus moveAgent(const GSID& idx,const GSNavPoint& targetPoint);
    GSStatus changeAgentSpeed(const GSID& idx,const int newSpeedx,const int newSpeedy);
    GSStatus stop(const GSID& idx);
    
    int m_maxAgents;
    GSNavAgent* m_agents;
};

#endif /* GSNavCrowd_hpp */
