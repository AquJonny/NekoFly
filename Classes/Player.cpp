#include "Player.h"
#include "Stage.hpp"

USING_NS_CC;

//角色动画帧数
const int FRAME_COUNT = 4;

//横向速度最大值
const int VELOCITY_LIMIT = 40;

//初期加速度
const Vec2 INITAL_ACCELERATION = Vec2(200, 0);

Player::Player()
{

}

Player::~Player()
{

}

bool Player::init()
{
    if(!Sprite::initWithFile("player.png"))
    {
        return false;
    }
    
    //
    auto frameSize = Size(this->getContentSize().width/FRAME_COUNT, this->getContentSize().height);
    
    //
    this->setTextureRect(Rect(0, 0, frameSize.width, frameSize.height));
    
    //
    Vector<SpriteFrame*> frames;
    
    for (int i = 0; i < FRAME_COUNT; i++)
    {
        auto frame = SpriteFrame::create("player.png",
                                         Rect((i*frameSize.width),
                                              0,
                                              frameSize.width,
                                              frameSize.height));
        
        frames.pushBack(frame);
    }
    
    //
    auto animetion = Animation::createWithSpriteFrames(frames);
    
    //
    animetion->setDelayPerUnit(0.05);
    
    //
    auto repAnimate = RepeatForever::create(Animate::create(animetion));
    
    //
    this->runAction(repAnimate);
    
    //
    auto physicsCircle = PhysicsBody::createCircle(frameSize.width/2.0);
    physicsCircle->setRotationEnable(false);
    this->setPhysicsBody(physicsCircle);
    
    //
    _acceleration = INITAL_ACCELERATION;
    
    this->scheduleUpdate();
    
    return true;
}

void Player::update(float dt)
{
    //
    this->getPhysicsBody()->applyImpulse(_acceleration);
    
    //
    auto v = this->getPhysicsBody()->getVelocity();
    
    if(v.x > VELOCITY_LIMIT)
    {
        v.x = VELOCITY_LIMIT;
        this->getPhysicsBody()->setVelocity(v);
    }
}
