#include "GSNavTestScene.h"

USING_NS_CC;
using namespace ui;

Scene* GSNavTestScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GSNavTestScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GSNavTestScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    _group = RadioButtonGroup::create();
    this->addChild(_group);
    
    const int column = 7;
    
    std::map<radioTypes,std::string> items;
    items[radioTypes::eAddAgent] = "添加\nAgent";
    items[radioTypes::eRemoveAgent] = "移除\nAgent";
    items[radioTypes::eAddObstacle] = "添加\nObstacle";
    items[radioTypes::eRemoveObstacle] = "移除\nObstacle";
    items[radioTypes::eSelectAll] = "全选";
    items[radioTypes::eSelect] = "选择";
    items[radioTypes::eMove] = "移动";
    
    for (int i = 0 ; i < items.size(); i++) {
        std::string text = items[(radioTypes)i];
        
        RadioButton* button = RadioButton::create("BgFrame.png", "chip_bg.png","chip_bg.png","","");
        button->setPosition(Vec2((i % column ) * 70 + 50,(i/column) * 70 + 100));
        _group->addRadioButton(button);
        
        Text *label = Text::create();
        label->setString(text);
        button->addChild(label);
        label->setPosition(Vec2(25,25));
        
        this->addChild(button);
    }
    
    _group->setSelectedButton(items.size() - 1);
    _group->addEventListener(CC_CALLBACK_3(GSNavTestScene::onChangedRadioButtonGroup1, this));
    
    widthTextField = TextField::create();
    heightTextField = TextField::create();
    
    widthTextField->setPlaceHolder("宽");
    heightTextField->setPlaceHolder("高");
    
    widthTextField->setString("50");
    heightTextField->setString("50");
    
    this->addChild(widthTextField);
    this->addChild(heightTextField);
    
    widthTextField->setPosition(Vec2(200,200));
    heightTextField->setPosition(Vec2(400,200));
    
    _drawNode = DrawNode::create();
    addChild(_drawNode);
    _drawNode->setPosition(Vec2((designResolutionSize.width - navMeshSize.width) / 2,(designResolutionSize.height - navMeshSize.height) / 2));
    
    GSPolygon polygon;
    polygon.points.push_back(GSNavPoint(0,0));
    polygon.points.push_back(GSNavPoint(0,navMeshSize.height));
    polygon.points.push_back(GSNavPoint(navMeshSize.width,navMeshSize.height));
    polygon.points.push_back(GSNavPoint(navMeshSize.width,0));
    _GSFind.createNavMesh(polygon);
    
    this->scheduleUpdate();
    
    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesBegan = CC_CALLBACK_2(GSNavTestScene::onTouchesBegan, this);
    listener->onTouchesMoved = CC_CALLBACK_2(GSNavTestScene::onTouchesMoved, this);
    listener->onTouchesEnded = CC_CALLBACK_2(GSNavTestScene::onTouchesEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}

void GSNavTestScene::update(float dt)
{
    _GSFind.update((int)(dt * 1000));
    gsNavDrawScene(_drawNode, _GSFind.getNavMesh(), _GSFind.getCrowd());
}

void GSNavTestScene::onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event)
{
}

void GSNavTestScene::onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event)
{
}

void GSNavTestScene::onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event)
{
    if(touches.size() <= 0){
        return;
    }
    
    Touch* touch = touches[0];
    Vec2 pos = touch->getLocation() - _drawNode->getPosition();
    log("点击：%f %f",pos.x,pos.y);
    
    float w = atof(widthTextField->getString().c_str());
    float h = atof(heightTextField->getString().c_str());
    
    int nowSelectIndex = _group->getSelectedButtonIndex();
    
    if(nowSelectIndex == radioTypes::eAddAgent){
        GSNavAgentParams param;
        param.w = w;
        param.h = h;
        param.m_speed = 1;
        GSID id;
        _GSFind.addAgent(GSNavPoint(pos.x,pos.y), param, id);
    }else if(nowSelectIndex == radioTypes::eRemoveAgent){
        
    }else if(nowSelectIndex == radioTypes::eAddObstacle){
        GSID id;
        _GSFind.addObstacle((int)pos.x,(int)pos.y,(int)w,(int)h, id);
//        _GSFind.addObstacle(489, 281, (int)w, (int)h, id);
    }else if(nowSelectIndex == radioTypes::eRemoveObstacle){
    
    }else if(nowSelectIndex == radioTypes::eSelect){
    
    }else if(nowSelectIndex == radioTypes::eSelectAll){
    
    }else if(nowSelectIndex == radioTypes::eMove){
        _GSFind.moveAgent(0, GSNavPoint(pos.x,pos.y));
    }
}

void GSNavTestScene::onChangedRadioButtonGroup1(RadioButton* radioButton, int index, cocos2d::ui::RadioButtonGroup::EventType type)
{
    log("选中:%d",index);
}
