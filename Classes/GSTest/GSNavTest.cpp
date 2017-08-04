//
//  GSNavTest.cpp
//  GSPathFind
//
//  Created by Can Wu on 2017/7/31.
//
//

#include "GSNavTest.hpp"

using namespace cocos2d;

void gsDrawPolygon(cocos2d::DrawNode* node,const GSPolygon& polygon,const cocos2d::Color4F &fillColor,float borderWidth , const cocos2d::Color4F &borderColor)
{
    size_t vertSize = polygon.points.size();
    Vec2 verts[vertSize];
    for(int i = 0 ; i < vertSize; i++){
        const GSNavPoint &point = polygon.points[i];
        verts[i] = Vec2(point.x,point.y);
    }
    node->drawPolygon(verts, vertSize, fillColor, borderWidth, borderColor);
}

void gsDrawNavPolygon(cocos2d::DrawNode* node,const GSNavPolygon& polygon,const cocos2d::Color4F &fillColor,float borderWidth , const cocos2d::Color4F &borderColor )
{
    size_t vertSize = polygon.edges.size();
    if(vertSize < 3){
        return;
    }
    Vec2 verts[vertSize];
    for(int i = 0 ; i < vertSize; i++){
        const GSNavPoint &point = polygon.edges[i].point;
        verts[i] = Vec2(point.x,point.y);
    }
    
    for(int i = 0; i < vertSize; i++){
        
        node->drawLine(verts[i], verts[(i+1)%polygon.edges.size()], Color4F(1,1,1,1));
    }
    
    node->drawPolygon(verts, vertSize, fillColor, borderWidth, borderColor);
}

void gsDrawLine(cocos2d::DrawNode* node,const GSNavPoint &point1, const GSNavPoint &point2,const Color4F &fillColor)
{
    node->drawLine(Vec2(point1.x,point1.y), Vec2(point2.x,point2.y),fillColor);
}

void gsNavDrawScene(cocos2d::DrawNode* node,GSNavMesh* mesh,GSNavCrowd* crowd)
{
    node->clear();
    
    //border
//    gsDrawNavPolygon(node, mesh->m_polygons[0],Color4F(1.0f, 1.0f, 1.0f, 0.0f), 2, Color4F(1.0f,1.0f,1.0f,1.0f));
    
    //obstacle
    for(int i = 0 ; i < mesh->m_polygons.size(); i ++){
        gsDrawNavPolygon(node, mesh->m_polygons[i], Color4F(1.0f,0.0f,0.0f,1.0f),0,Color4F(0,0,0,0));
    }
    
    //entity
    for(int i = 0 ; i < crowd->m_maxAgents;i++){
        GSNavAgent* agent = &crowd->m_agents[i];
        
        if(agent->m_active == false){
            continue;
        }
        
        Color4F color = Color4F(1, 1, 1, 1);
        if(agent->m_state == GSNavAgentState::eNone){
        
        }else if(agent->m_state == GSNavAgentState::eFindTarget){
            color = Color4F(0,0,1,1);
        }else if(agent->m_state == GSNavAgentState::eMoving){
            color = Color4F(0,1,0,1);
        }else if(agent->m_state == GSNavAgentState::eFinishMove){
            color = Color4F(0,0,1,1);
        }
        
        GSPolygon polygon;
        polygon.points.push_back(GSNavPoint(agent->m_pos.x - agent->m_param.w / 2 , agent->m_pos.y - agent->m_param.h / 2));
        polygon.points.push_back(GSNavPoint(agent->m_pos.x + agent->m_param.w / 2 , agent->m_pos.y - agent->m_param.h / 2));
        polygon.points.push_back(GSNavPoint(agent->m_pos.x + agent->m_param.w / 2 , agent->m_pos.y + agent->m_param.h / 2));
        polygon.points.push_back(GSNavPoint(agent->m_pos.x - agent->m_param.w / 2 , agent->m_pos.y + agent->m_param.h / 2));
        gsDrawPolygon(node, polygon, color, 0, Color4F(0, 0, 0, 0));
    }
    
    //navMesh
}
