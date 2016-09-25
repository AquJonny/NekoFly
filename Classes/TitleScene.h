#ifndef __TITLE_SCENE_H__
#define __TITLE_SCENE_H__

#include "cocos2d.h"
#include "MainScene.h"

class TitleScene : public cocos2d::Layer
{
protected:
    
    TitleScene();
    
    virtual ~TitleScene();
    
    bool init() override;

public:
    
    static cocos2d::Scene* createScene();
    
    void update(float dt) override;
    
    CREATE_FUNC(TitleScene);
    
    void onEnterTransitionDidFinish() override;

};

#endif // __TITLE_SCENE_H__
