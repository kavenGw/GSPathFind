//
//  GSCrowed.cpp
//  GSPathFind
//
//  Created by Can Wu on 2017/7/27.
//
//

#include "GSNavCrowd.hpp"
#include "GSAlloc.hpp"

///GSNavAgent
GSNavAgent::GSNavAgent()
{
    
}

GSNavAgent::~GSNavAgent()
{

}


///GSNavCrowd
GSNavCrowd::GSNavCrowd():
m_maxAgents(0),
m_agents(0)
{
}

GSNavCrowd::~GSNavCrowd()
{
    for (int i = 0; i < m_maxAgents; ++i)
        m_agents[i].~GSNavAgent();
    gsFree(m_agents);
}

GSStatus GSNavCrowd::init(int maxAgent)
{
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
    
    memcpy(&(agent->m_param), &param, sizeof(GSNavAgentParams));
    
    agent->m_active = true;
    
    return GS_SUCCESS;
}

GSStatus GSNavCrowd::removeAgent(const GSID& idx)
{
    GSNavAgent* agent = getNavAgent(idx);
    
    if(agent == NULL || agent->m_active == false){
        return GS_FAILURE;
    }
    
    return  GS_SUCCESS;
}
