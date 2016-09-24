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
    
    //由于一张图“play.png”中包涵了四帧动画，所以提取每帧动画的尺寸时，宽除以4
    auto frameSize = Size(this->getContentSize().width/FRAME_COUNT, this->getContentSize().height);
    
    //设置sprite的纹理尺寸为第一张动画的范围
    this->setTextureRect(Rect(0, 0, frameSize.width, frameSize.height));
    
    //将“play.png”切割为4幅，保存至frames中
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
    
    //使用动画帧创建animetion(打包)
    auto animetion = Animation::createWithSpriteFrames(frames);
    
    //每帧动画之间间隔0.05秒
    animetion->setDelayPerUnit(0.05);
    
    //创建animate(动画)，并永远循环
    auto repAnimate = RepeatForever::create(Animate::create(animetion));
    
    //Sprite运行动画
    this->runAction(repAnimate);
    
    //创建刚体，设置其不可旋转
    auto physicsCircle = PhysicsBody::createCircle(frameSize.width/2.0);
    physicsCircle->setRotationEnable(false);
    
    //刚体的碰撞配置
    physicsCircle->setCategoryBitmask(static_cast<int>(Stage::TileType::Player));
    physicsCircle->setCollisionBitmask(static_cast<int>(Stage::TileType::Wall));
    physicsCircle->setContactTestBitmask(INT_MAX);
    
    this->setPhysicsBody(physicsCircle);
    
    //设置初期加速度
    _acceleration = INITAL_ACCELERATION;
    
    this->scheduleUpdate();
    
    return true;
}

void Player::update(float dt)
{
    //叠加矢量速度
    this->getPhysicsBody()->applyImpulse(_acceleration);
    
    //获得该物理刚体的速度参数
    auto v = this->getPhysicsBody()->getVelocity();
    
    if(v.x > VELOCITY_LIMIT)
    {
        //如果横向参数大于最大值，则限制
        v.x = VELOCITY_LIMIT;
        this->getPhysicsBody()->setVelocity(v);
    }
}
