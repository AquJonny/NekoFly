#include "MainScene.h"

USING_NS_CC;

#define __PJ_DEBUG__

//重力参数 ※(0,-3)是什么意思??
const Vec2 PHYSICS_ENGINE_GRAVITY = Vec2(0, -3);

//速度参数 ※6.0是什么意思??
const float PHYSICS_ENGINE_SPEED = 6.0;

//构造函数
MainScene::MainScene()
{
    
}

//析构函数
MainScene::~MainScene()
{
    
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
    
}

//Updata函数
void MainScene::update(float dt)
{
    
}

