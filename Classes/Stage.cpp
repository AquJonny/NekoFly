//
//  Stage.cpp
//  NekoFly
//
//  Created by Xuhao on 16/9/17.
//
//

#include "Stage.hpp"

USING_NS_CC;

Stage::Stage()
:_StageMap(nullptr)
,_player(nullptr)
{

}

Stage::~Stage()
{

    CC_SAFE_RELEASE_NULL(_StageMap);
    CC_SAFE_RELEASE_NULL(_player);
    
}

bool Stage::init()
{
    if(!Layer::init())
    {
        return false;
    }
    
    //创建TMXTiledMap地图对象，并加入当前Layer层。
    auto stagemap = TMXTiledMap::create("stage1.tmx");
    this->setStageMap(stagemap);
    this->addChild(stagemap);
    
    //
    auto terrainLayer = stagemap->getLayer("Terrain");
    auto objectLayer  = stagemap->getLayer("Object");
    
    //
    auto mapSize = stagemap->getMapSize();
    
    //
    for (int width = 0; width < mapSize.width; width++)
    {
        for (int height = 0; height < mapSize.height ; height++)
        {
            auto point = cocos2d::Vec2(width, height);
            Stage::addPhysicsBody(terrainLayer, point);
            Stage::addPhysicsBody(objectLayer, point);
        }
    }
    
    //
    auto player = Player::create();
    player->setPosition(Point(40, 160));
    this->setplayer(player);
    this->addChild(player);
    
    
    this->scheduleUpdate();
    
    return true;
}

void Stage::update(float dt)
{

}

cocos2d::Sprite* Stage::addPhysicsBody(cocos2d::TMXLayer* Layer, cocos2d::Vec2& point)
{
    auto sprite = Layer->getTileAt(point);
    
    if (sprite)
    {
        //创建物理材料，该材料包含三个参数 ＊各个参数的作用？
        //density：密度
        //restitution：弹性
        //friction：摩擦
        auto material = PhysicsMaterial();
        material.friction = 0;
        
        //创建PhysicsBox，区域是sprite，使用的材料是material
        auto physicsBox = PhysicsBody::createBox(sprite->getContentSize(), material);
        
        //该physicsbox是否活动 false＝>固定，true=>可动（会收到重力，碰撞等影响）
        physicsBox->setDynamic(false);
        
        //设置锚点居中
        sprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        
        //给sprite加载physicsbox
        sprite->setPhysicsBody(physicsBox);
        
        return sprite;
    }
    else
    {
        return nullptr;
    }
    
}
