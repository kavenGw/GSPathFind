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
    
    RadioButtonGroup *group = RadioButtonGroup::create();
    this->addChild(group);
    
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
        group->addRadioButton(button);
        
        Text *label = Text::create();
        label->setString(text);
        button->addChild(label);
        label->setPosition(Vec2(25,25));
        
        this->addChild(button);
    }
    
    group->setSelectedButton(items.size() - 1);
    group->addEventListener(CC_CALLBACK_3(GSNavTestScene::onChangedRadioButtonGroup1, this));
    
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
    
    return true;
}

void GSNavTestScene::update(float dt)
{
    _GSFind.update((int)(dt * 1000));
    gsNavDrawScene(_drawNode, _GSFind.getNameMesh());
}

void GSNavTestScene::onChangedRadioButtonGroup1(RadioButton* radioButton, int index, cocos2d::ui::RadioButtonGroup::EventType type)
{
    log("选中:%d",index);
}
