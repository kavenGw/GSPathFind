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
    Vec2 verts[vertSize];
    for(int i = 0 ; i < vertSize; i++){
        const GSNavPoint &point = polygon.edges[i].point;
        verts[i] = Vec2(point.x,point.y);
    }
    node->drawPolygon(verts, vertSize, fillColor, borderWidth, borderColor);
}

void gsDrawLine(cocos2d::DrawNode* node,const GSNavPoint &point1, const GSNavPoint &point2,const Color4F &fillColor)
{
    node->drawLine(Vec2(point1.x,point1.y), Vec2(point2.x,point2.y),fillColor);
}

void gsNavDrawScene(cocos2d::DrawNode* node,GSNavMesh* mesh)
{
    node->clear();
    
    //border
    gsDrawPolygon(node, mesh->m_polygon,Color4F(1.0f, 1.0f, 1.0f, 0.0f), 2, Color4F(1.0f,1.0f,1.0f,1.0f));
    
    //obstacle
    for(int i = 0 ; i < mesh->m_polygons.size(); i ++){
        gsDrawNavPolygon(node, mesh->m_polygons[i], Color4F(1.0f,0.0f,0.0f,1.0f),0,Color4F(0,0,0,0));
    }
    
    //entity
    
    
    //navMesh
}
