#include "MainScene.h"

USING_NS_CC;

#define __PJ_DEBUG__

//�������� ��(0,-3)��ʲô��˼??
const Vec2 PHYSICS_ENGINE_GRAVITY = Vec2(0, -3);

//�ٶȲ��� ��6.0��ʲô��˼??
const float PHYSICS_ENGINE_SPEED = 6.0;

//���캯��
MainScene::MainScene()
{
	
}

//��������
MainScene::~MainScene()
{
	
}

//Create����
Scene* MainScene::createScene()
{
	auto scene = Scene::createWithPhysics();
	auto world = scene->getPysicsWorld();
	world->setGravity( PHYSICS_ENGINE_GRAVITY );
	world->setSpeed( PHYSICS_ENGINE_SPEED );
	
#ifdef __PJ_DEBUG__

	world->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

#endif
	
	auto layer = MainScene::create();
	
	scene->addChild(layer);
	
	return scene;
}

//���ڻ�����
bool MainScene::init()
{
	
}

//Updata����
void MainScene::update(float dt)
{
	
}

