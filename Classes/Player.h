#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "cocos2d.h"

class Player : public cocos2d::Sprite
{
protected:
    Player();
    
    virtual ~Player();
    
    bool init() override;
    
public:
    
    void update(float dt) override;
    
    //设置加速度参数 ＊为何要用容器
    //第一次看见的声明对象方法 什么作用？
    //声明指针出错了 why？
    CC_SYNTHESIZE_PASS_BY_REF(cocos2d::Vec2, _acceleration, acceleration);
    
    CREATE_FUNC(Player);
    

};

#endif // __PLAYER_H__
