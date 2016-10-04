#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "cocos2d.h"
#include "Stage.hpp"
#include "SimpleAudioEngine.h"
#include "TitleScene.h"


//重力参数 ※(0,-3)是什么意思?? -> x,y 正值为往右往上，负值为往左往下
const cocos2d::Vec2 PHYSICS_ENGINE_GRAVITY = cocos2d::Vec2(0, -3);

//浮力参数 ※(0，180)
const cocos2d::Vec2 PHYSICS_ENGINE_IMPLUSE = cocos2d::Vec2(0, 50);

//速度参数 ※6.0是什么意思??
const float PHYSICS_ENGINE_SPEED = 6.0;

const int ZORDER_BACKGROUND = 0;
const int ZORDER_STAGE = 1;
const int ZORDER_PLAYER = 2;
const int ZORDER_MENU = 3;

const int MAX_STAGE_LEVEL = 4;

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
    CC_SYNTHESIZE_RETAIN(cocos2d::Label*, _coinLabel, coinLabel);
    
    //创建视差节点，用作背景层的滚动显示
    CC_SYNTHESIZE_RETAIN(cocos2d::ParallaxNode*, _bkground, bkground);
    
    CC_SYNTHESIZE(short, _coin, coin);
    CC_SYNTHESIZE(bool, _IsTouch, IsTouch);
    
	//CREATE_FUNC(MainScene);
    static cocos2d::Scene* createWithLevel(int level);
    
    void onEnterTransitionDidFinish() override;
    
private:
    void GameFail();
    void GameFinish();

};

#endif // __MAIN_SCENE_H__
