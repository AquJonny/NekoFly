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
    
    auto winSize = Director::getInstance()->getWinSize();
    
    //创建TMXTiledMap地图对象，并加入当前Layer层。
    auto stagemap = TMXTiledMap::create("stage1.tmx");
    this->setStageMap(stagemap);
    this->addChild(stagemap);
    
    //获取TiledMap中的图层
    auto terrainLayer = stagemap->getLayer("Terrain");
    auto objectLayer  = stagemap->getLayer("Object");
    
    //获取TiledMap的地图尺寸信息
    auto mapSize = stagemap->getMapSize();
    
    //遍历地图中每一个图块，为其添加物理刚体
    for (int width = 0; width < mapSize.width; width++)
    {
        for (int height = 0; height < mapSize.height ; height++)
        {
            auto point = cocos2d::Vec2(width, height);
            Stage::addPhysicsBody(terrainLayer, point);
            Stage::addPhysicsBody(objectLayer, point);
        }
    }
    
    //设置Sprite
    auto player = Player::create();
    player->setPosition(Point(40, winSize.height/2.0));
    this->setplayer(player);
    this->addChild(player);
    
    //追随动作，追踪某个Node，在一定范围Rect内
    //不过屏幕会显示地图范围之外的区域，需要边界判断优化?
    auto follow = Follow::create(player, Rect(0,
                                              0,
                                              stagemap->getContentSize().width,
                                              stagemap->getContentSize().height));
    
    this->runAction(follow);
    
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
        
        //给sprite加载刚体
        sprite->setPhysicsBody(physicsBox);
        
        return sprite;
    }
    else
    {
        return nullptr;
    }
    
}
