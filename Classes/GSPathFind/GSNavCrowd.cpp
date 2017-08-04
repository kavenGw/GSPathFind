//
//  GSCrowed.cpp
//  GSPathFind
//
//  Created by Can Wu on 2017/7/27.
//
//

#include "GSNavCrowd.hpp"
#include "GSAlloc.hpp"
#include "GSNavMath.hpp"
#include <string.h>

//GSNavAgentParams
GSNavAgentParams::GSNavAgentParams():
w(0),
h(0),
m_speed(0)
{
    
}

///GSNavAgent
GSNavAgent::GSNavAgent():
m_active(false),
m_id(0),
m_pos(0,0),
m_targetPos(0,0),
m_leftSpeed(0),
m_leftPos(0,0),
m_state(GSNavAgentState::eNone)
{
    
}

GSNavAgent::~GSNavAgent()
{

}

GSNavPoint GSNavAgent::getNextTargetPoint()
{
    if(m_paths.size() > 0){
        return m_paths[m_paths.size()-1];
    }
    
    return m_targetPos;
}


///GSNavCrowd
GSNavCrowd::GSNavCrowd():
m_maxAgents(0),
m_agents(0),
m_mesh(0)
{
}

GSNavCrowd::~GSNavCrowd()
{
    for (int i = 0; i < m_maxAgents; ++i)
        m_agents[i].~GSNavAgent();
    gsFree(m_agents);
}

GSStatus GSNavCrowd::init(GSNavMesh* p_mesh,int maxAgent)
{
    this->m_mesh = p_mesh;
    
    this->m_maxAgents = maxAgent;
    m_agents = (GSNavAgent*)gsAlloc(sizeof(GSNavAgent)*this->m_maxAgents);
    if (!m_agents){
        return GS_FAILURE;
    }
    
    for (int i = 0; i < m_maxAgents; ++i)
    {
        new(&m_agents[i]) GSNavAgent();
        m_agents[i].m_active = false;
    }
    
    return GS_SUCCESS;
}

/*
 tick (ms)
 */
void GSNavCrowd::update(int tick)
{
    for (int i = 0 ; i < m_maxAgents; i++) {
        GSNavAgent* agent = getNavAgent(i);
        
        if(agent->m_active == false){
            continue;
        }
 
        if(agent->m_state == GSNavAgentState::eFindTarget){
            m_mesh->findPath(agent->m_pos, agent->m_targetPos, agent->m_paths);
            agent->m_state = GSNavAgentState::eMoving;
            agent->m_leftPos = GSNavPoint(0,0);
            agent->m_leftSpeed = 0;
        }
        
        if(agent->m_state == GSNavAgentState::eNone){
            
        }else if(agent->m_state == GSNavAgentState::eMoving){
            if(agent->m_paths.size() == 0){
                agent->m_state = GSNavAgentState::eFinishMove;
            }else{
                if(gsMove(agent->m_pos, agent->getNextTargetPoint(), agent->m_leftSpeed, agent->m_leftPos, agent->m_param.m_speed,tick)){
                    agent->m_paths.erase(agent->m_paths.end()-1);
                }
            }
        }else if(agent->m_state == GSNavAgentState::eFinishMove){
            
        }
    }
}

GSNavAgent* GSNavCrowd::getNavAgent(const GSID& idx)
{
    if(idx < 0 || idx >= m_maxAgents){
        return NULL;
    }
    
    return &m_agents[idx];
}

GSStatus GSNavCrowd::addAgent(const GSNavPoint& point,const GSNavAgentParams& param,GSID &idx)
{
    if(param.w == 0 || param.h == 0){
        return GS_FAILURE;
    }
    
    idx = -1;
    for (int i = 0; i < m_maxAgents; ++i)
    {
        if (!m_agents[i].m_active)
        {
            idx = i;
            break;
        }
    }
    if (idx == -1)
        return GS_FAILURE;
    
    GSNavAgent* agent = getNavAgent(idx);
    agent->m_id = idx;
    
    memcpy(&(agent->m_param), &param, sizeof(GSNavAgentParams));
    
    agent->m_active = true;
    agent->m_leftSpeed = 0;
    agent->m_pos = point;
    
    return GS_SUCCESS;
}

GSStatus GSNavCrowd::removeAgent(const GSID& idx)
{
    GSNavAgent* agent = getNavAgent(idx);
    
    if(agent == NULL || agent->m_active == false){
        return GS_FAILURE;
    }
    
    agent->m_active = false;
    
    return  GS_SUCCESS;
}

GSStatus GSNavCrowd::moveAgent(const GSID& idx,const GSNavPoint& targetPoint)
{
    GSNavAgent* agent = getNavAgent(idx);
    
    if(agent == NULL || agent->m_active == false){
        return GS_FAILURE;
    }
    
    agent->m_targetPos = targetPoint;
    
    agent->m_state = GSNavAgentState::eFindTarget;
    
    return  GS_SUCCESS;
}


GSStatus GSNavCrowd::changeAgentSpeed(const GSID& idx,const int newSpeedx,const int newSpeedy)
{
    
    GSNavAgent* agent = getNavAgent(idx);
    
    if(agent == NULL || agent->m_active == false){
        return GS_FAILURE;
    }
    
    agent->m_param.m_speed = GSNavPoint(newSpeedx,newSpeedy);
    
    return GS_SUCCESS;
}

GSStatus GSNavCrowd::stop(const GSID& idx)
{
    
    GSNavAgent* agent = getNavAgent(idx);
    
    if(agent == NULL || agent->m_active == false){
        return GS_FAILURE;
    }
    
    agent->m_state = eNone;

    return GS_SUCCESS;
}
