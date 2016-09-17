#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "cocos2d.h"
#include "Stage.hpp"

class MainScene : public cocos2d::Layer
{
protected:

	MainScene();
	
	virtual ~MainScene();
	
	bool init() override;

public:

	static cocos2d::Scene* createScene();

	void update(float dt) override;

    CC_SYNTHESIZE_RETAIN(Stage*, _stage, stage);
    
	CREATE_FUNC(MainScene);

};

#endif // __MAIN_SCENE_H__
