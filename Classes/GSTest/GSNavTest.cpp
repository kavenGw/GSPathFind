//
//  GSNavTest.cpp
//  GSPathFind
//
//  Created by Can Wu on 2017/7/31.
//
//

#include "GSNavTest.hpp"

using namespace cocos2d;

void gsDrawPolygon(cocos2d::DrawNode* node,const GSPolygon& polygon,const Color4F &fillColor,float borderWidth, const Color4F &borderColor)
{
    size_t vertSize = polygon.points.size();
    Vec2 verts[vertSize];
    for(int i = 0 ; i < vertSize; i++){
        const GSNavPoint &point = polygon.points[i];
        verts[i] = Vec2(point.x,point.y);
    }
    node->drawPolygon(verts, vertSize, fillColor, borderWidth, borderColor);
}

void gsNavDrawScene(cocos2d::DrawNode* node,GSNavMesh* mesh)
{
    node->clear();
    
    //border
    gsDrawPolygon(node, mesh->getBornderPolygon(),Color4F(1.0f, 1.0f, 1.0f, 0.0f), 2, Color4F(1.0f,1.0f,1.0f,1.0f));
    
    //entity
    
    //obstacle
    
    //navMesh
}
