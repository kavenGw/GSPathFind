#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "ui/UIRadioButton.h"
#include "ui/UIText.h"
#include "ui/UITextField.h"
#include "GSPathFind.hpp"
#include "GSNavTest.hpp"
#include "ui/UILayout.h"

static cocos2d::Size designResolutionSize = cocos2d::Size(640, 960);
static cocos2d::Size smallResolutionSize = cocos2d::Size(640, 960);
static cocos2d::Size mediumResolutionSize = cocos2d::Size(1024, 768);
static cocos2d::Size largeResolutionSize = cocos2d::Size(2048, 1536);

static cocos2d::Size navMeshSize = cocos2d::Size(800, 500);
enum radioTypes
{
    eAddAgent = 0,
    eRemoveAgent,
    eAddObstacle,
    eRemoveObstacle,
    eSelectAll,
    eSelect,
    eMove,
};

class GSNavTestScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void onChangedRadioButtonGroup1(cocos2d::ui::RadioButton* radioButton, int index, cocos2d::ui::RadioButtonGroup::EventType type);
    
    // implement the "static create()" method manually
    CREATE_FUNC(GSNavTestScene);
    
    void update(float dt);
    
    void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
private:
    GSPathFind _GSFind;
    cocos2d::DrawNode* _drawNode;
    cocos2d::ui::TextField* widthTextField;
    cocos2d::ui::TextField* heightTextField;
    cocos2d::ui::RadioButtonGroup* _group;
};

#endif // __HELLOWORLD_SCENE_H__
