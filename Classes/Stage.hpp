//
//  Stage.hpp
//  NekoFly
//
//  Created by Xuhao on 16/9/17.
//
//

#ifndef Stage_hpp
#define Stage_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "Player.h"
#include "SimpleAudioEngine.h"

class Stage : public cocos2d::Layer
{
protected:
    Stage();
    virtual ~Stage();
    //bool init() override;
    bool initWithLevel(int level);
    
public:
    void update(float dt) override;

    //CREATE_FUNC(Stage);
    static Stage* creatWithLevel(int level);
    
    CC_SYNTHESIZE_READONLY(int, _level, level);
    
    CC_SYNTHESIZE_RETAIN(cocos2d::TMXTiledMap*, _StageMap, StageMap);
    
    CC_SYNTHESIZE_RETAIN(cocos2d::Sprite*, _player, player);
    
    //给制定Layer的特定坐标点图块设置刚体
    //如果指定坐标位置没有图块存在，则返回nullptr
    //@param  对象layer           //通过TMXTiledMap的getLayer方法获得，参数为layer名（创建地图时定义了）
    //@param  对象图块的地图上的坐标  //如何确定坐标系？=> 创建地图文件时候的区块数字作为坐标系
    //@return 图块的Sprite指针 or nullptr
    cocos2d::Sprite* addPhysicsBody(cocos2d::TMXLayer* layer, cocos2d::Vec2& point);
    
    enum class TileType
    {
        Wall   = 1 << 0,    //墙壁
        Player = 1 << 1,    //人物
        Enemy  = 1 << 2,    //敌人
        Coin   = 1 << 3,    //金币
        
        COUNT_MAX           //计数最大值
    };

private:

};


#endif /* Stage_hpp */
