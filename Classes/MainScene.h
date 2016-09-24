#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "cocos2d.h"
#include "Stage.hpp"

//重力参数 ※(0,-3)是什么意思?? -> x,y 正值为往右往上，负值为往左往下
const cocos2d::Vec2 PHYSICS_ENGINE_GRAVITY = cocos2d::Vec2(0, -3);

//浮力参数 ※(0，180)
const cocos2d::Vec2 PHYSICS_ENGINE_IMPLUSE = cocos2d::Vec2(0, 180);

//速度参数 ※6.0是什么意思??
const float PHYSICS_ENGINE_SPEED = 6.0;

const int ZORDER_BACKGROUND = 0;
const int ZORDER_STAGE = 1;
const int ZORDER_PLAYER = 2;
const int ZORDER_MENU = 3;

class MainScene : public cocos2d::Layer
{
protected:

	MainScene();
	
	virtual ~MainScene();
	
	//bool init() override;
    bool initWithLevel(int level);
    
public:
    
	static cocos2d::Scene* createScene();

	void update(float dt) override;
    
    CC_SYNTHESIZE_RETAIN(Stage*, _stage, stage);

    CC_SYNTHESIZE(bool, _IsTouch, IsTouch);
    
	//CREATE_FUNC(MainScene);
    static cocos2d::Scene* createWithLevel(int level);
    
private:
    void GameFail();

};

#endif // __MAIN_SCENE_H__
