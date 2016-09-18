#include "MainScene.h"

USING_NS_CC;

#define __PJ_DEBUG__

//重力参数 ※(0,-3)是什么意思??
const Vec2 PHYSICS_ENGINE_GRAVITY = Vec2(0, -3);

//
const Vec2 PHYSICS_ENGINE_IMPLUSE = Vec2(0, 180);

//速度参数 ※6.0是什么意思??
const float PHYSICS_ENGINE_SPEED = 6.0;

//构造函数
MainScene::MainScene()
:_stage(nullptr)
,_IsTouch(false)
{
    
}

//析构函数
MainScene::~MainScene()
{
    CC_SAFE_RELEASE_NULL(_stage);
}

//Create函数
Scene* MainScene::createScene()
{
    auto scene = Scene::createWithPhysics();
    auto world = scene->getPhysicsWorld();
    world->setGravity( PHYSICS_ENGINE_GRAVITY );
    world->setSpeed( PHYSICS_ENGINE_SPEED );
    
#ifdef __PJ_DEBUG__
    
    world->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    
#endif
    
    auto layer = MainScene::create();
    
    scene->addChild(layer);
    
    return scene;
}

//初期化函数
bool MainScene::init()
{
    if(!Layer::init())
    {
        return false;
    }
    
    auto winsize = Director::getInstance()->getWinSize();
    
    log("WinSize: %f,%f", winsize.width, winsize.height);
    
    /*create Sprite for test*/
    /*
    auto sprite = Sprite::create("coin.png");
    //创建和精灵同等大小的刚体
    //刚体为方形，可以用不同方法创建例如圆形等别的形状的刚体
    //PhysicsBody类中定义了很多针对刚体的设定，动作，定义的方法
    auto physicsBody = PhysicsBody::createBox(sprite->getContentSize());
    //为精灵设定刚体
    sprite->setPhysicsBody(physicsBody);
    
    sprite->setPosition(Point(winsize.width/2.0, winsize.height/2.0));
    this->addChild(sprite);
    */
    /*
    实验效果，被创建的精灵会自动下落
    */
    
    //创建Layer对象－－stage
    //Layer不会随着屏幕适配进行缩放。如何解决？？
    auto stage = Stage::create();
    
    this->setstage(stage);
    this->addChild(stage);
    
    //
    auto TouchEvent = EventListenerTouchOneByOne::create();
    
    TouchEvent->onTouchBegan =
    [this](Touch* touch, Event* event)
    {
        this->setIsTouch(true);
        
        return true;
    };
    
    TouchEvent->onTouchMoved =
    [this](Touch* touch,Event* event)
    {
        this->setIsTouch(false);
    };
    
    TouchEvent->onTouchEnded =
    [this](Touch* touch,Event* event)
    {
        this->setIsTouch(false);
    };
    
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(TouchEvent, this);
    
    this->scheduleUpdate();
    
    return true;
}

//Updata函数
void MainScene::update(float dt)
{
    if (this->getIsTouch())
    {
        //
        _stage->getplayer()->getPhysicsBody()->applyImpulse(PHYSICS_ENGINE_IMPLUSE);
        
    }
    
    
}

