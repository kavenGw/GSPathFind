//
//  GSNavTest.hpp
//  GSPathFind
//
//  Created by Can Wu on 2017/7/31.
//
//

#ifndef GSNavTest_hpp
#define GSNavTest_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "GSNavMesh.hpp"

void gsNavDrawScene(cocos2d::DrawNode* node,GSNavMesh* mesh);
void gsDrawLine(cocos2d::DrawNode* node,const GSNavPoint &point1, const GSNavPoint &point2,const cocos2d::Color4F &fillColor);
void gsDrawPolygon(cocos2d::DrawNode* node,const GSPolygon& polygon,const cocos2d::Color4F &fillColor,float borderWidth , const cocos2d::Color4F &borderColor);
void gsDrawNavPolygon(cocos2d::DrawNode* node,const GSNavPolygon& polygon,const cocos2d::Color4F &fillColor,float borderWidth , const cocos2d::Color4F &borderColor );
#endif /* GSNavTest_hpp */
