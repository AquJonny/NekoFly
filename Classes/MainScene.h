#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "cocos2d.h"

class MainScene : public cocos2d::Layer
{
protected:

	MainScene();
	
	virtual ~MainScene();
	
	bool init() override;

public:

	static cocos2d::Scene* createScene();

	void update(float dt) override;

	CREATE_FUNC(MainScene);

};

#endif // __MAIN_SCENE_H__
