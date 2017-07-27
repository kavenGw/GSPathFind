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

class GSNavAgentParams
{
    int w;
    int h;
};

class GSNavAgent
{
public:
    bool m_active;
    GSID m_id;
    GSNavPoint m_pos;
    GSNavPoint m_targetPos;
    
    GSNavAgentParams m_param;
    
    GSNavAgent();
    ~GSNavAgent();
};

class GSNavCrowd
{
private:
    int m_maxAgents;
    GSNavAgent* m_agents;
public:
    GSNavCrowd();
    ~GSNavCrowd();
    
    GSStatus init(const int maxAgent);
    void update(const int tick);
    
    GSNavAgent* getNavAgent(const GSID& idx);
    GSStatus addAgent(const GSNavPoint& point,const GSNavAgentParams& param,GSID &idx);
    GSStatus removeAgent(const GSID& idx);
    
    
};

#endif /* GSNavCrowd_hpp */
