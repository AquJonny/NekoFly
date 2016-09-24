#include "MainScene.h"

USING_NS_CC;

#define _NO_PJ_DEBUG__

//构造函数
MainScene::MainScene()
:_stage(nullptr)
,_IsTouch(false)
{
    
}

//析构函数
MainScene::~MainScene()
{
    CC_SAFE_RELEASE_NULL(_stage);
}

//Create函数
//Scene* MainScene::createScene()
Scene* MainScene::createWithLevel(int level)
{
    auto scene = Scene::createWithPhysics();
    auto world = scene->getPhysicsWorld();
    world->setGravity( PHYSICS_ENGINE_GRAVITY );
    world->setSpeed( PHYSICS_ENGINE_SPEED );
    
#ifdef __PJ_DEBUG__
    
    world->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    
#endif
    
    //auto layer = MainScene::create();
    auto layer = new MainScene();
    if(layer->initWithLevel(level))
    {
        layer->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(layer);
    }
    
    scene->addChild(layer, ZORDER_BACKGROUND);
    
    /*
    创建带有物理引擎效果的世界
    ＊想象一下，现实的世界中。
    ＊Scene是地球，地球的重力决定了存在于地球上的所有物体所受到的重力(Gravity)和加速度(Speed)
    ＊Layer是大陆板块，是一个拥有边界的实际存在的对象(尽管它很大，也是有边界的)
    ＊Sprite是在这个大陆上存在的山，河，湖，树木，物体，人等等...
      它们都拥有着各自特有的性质，而这些性质都是根据其材料
      (PhysicsMaterial)决定的。
        //创建物理材料(PhysicsMaterial)，该材料包含三个参数
        //density：密度        ->密度越高，等体积时候的质量越大，受到重力和加速度影响就越大
        //restitution：弹性    ->0～1.0的系数，1.0时会产生完全反弹(作用对象是双方)
        //friction：摩擦       ->0～1.0的系数，1.0时会产生很大摩擦力
    ＊有了材料之后，就可以创建一个个物体了(山，河，湖，树木，物体，人...)
      作为一个个物体，它们也有自己的特性
        //是否是动态的(受重力，冲击，碰撞影响) 默认是true，一般山，河，湖，树木这类场景类的物体都会设置成不动
        //是否会旋转(受到碰撞，重力影响) 默认是true，如果非动态，则不会旋转
        //质量(mass),力矩(moment)，速度(velocity)，角速度(AngularVelocity)，线性阻力(LinearDamping)
        //角阻力(AngularDamping)这些特性都是可以被改变的，动作过程中通过方法去改变其运动状态
        //施加持续的力(applyForce)
          力，循序渐进——ApplyForce
          顾名思义，ApplyForce方法会在刚体上施加一个力。
          学过物理力学的同学都知道，F=ma，有了力F就有了加速度a，有了加速度，物体就会有速度，就会慢慢动起来。
          (但是不会立马动起来，因为力不会直接影响速度)。
     
        //施加一个冲量(applyImpulse)
          速度，叠加——ApplyImpulse
          与ApplyForce不同，ApplyImpulse不会产生力，而是直接影响刚体的速度。
          通过ApplyImpulse方法添加的速度会与刚体原有的速度叠加，产生新的速度。
     
        //设置速度(setVelocity)
          一触即发——SetVelocity
          setVelocity与ApplyImpulse一样，直接影响刚体的速度。
          不一样的是，setVelocity添加的速度会覆盖刚体原有的速度。
     
        //施加一个扭力(applyTorque)
        //速度，角速度会被它们影响
     
     1.使用Scene::createWithPhysics()方法创建一个带有物理引擎的Scene
       在该Scene中加载的Layer和Sprite就会适用于物理法则(重力与加速度)
     2.使用PhysicsMaterial()方法创建一个材料参数(可以不设置，使用默认材料->0密度，0摩擦，0弹性)
     3.使用PhysicsBody::createEdgeBox()方法创建一个空心的方形区域，其大小就是边界，
       设立边界的理由是防止在这个物理世界中的Sprites无休止的下落，上升，前冲等超出目视范围的行为
       ＊本例中，使用了地图参数，对地图的边界物体添加刚体效果同样也达到了将范围圈起来的作用，
         所以不用另外再次创建空心方形。
     4.使用PhysicsBody::createXXXXXXX()系列方法创造自己需要的物理实体(圆形，方形，多边形...)
     5.通过对Sprites的物理实体进行［力，速度］的操作，来改变其运行方式(前进，后退，上升，下降，旋转)
    */
    
    return scene;
}

//初期化函数
//bool MainScene::init()
bool MainScene::initWithLevel(int level)
{
    if(!Layer::init())
    {
        return false;
    }
    
    auto WinSize = Director::getInstance()->getWinSize();
    
    log("WinSize: %f,%f", WinSize.width, WinSize.height);
    
    /*create Sprite for test*/
    /*
    auto sprite = Sprite::create("coin.png");
    //创建和精灵同等大小的刚体
    //刚体为方形，可以用不同方法创建例如圆形等别的形状的刚体
    //PhysicsBody类中定义了很多针对刚体的设定，动作，定义的方法
    auto physicsBody = PhysicsBody::createBox(sprite->getContentSize());
    //为精灵设定刚体
    sprite->setPhysicsBody(physicsBody);
    
    sprite->setPosition(Point(winsize.width/2.0, winsize.height/2.0));
    this->addChild(sprite);
    */
    /*
    实验效果，被创建的精灵会自动下落，而且掉出屏幕
    */
    
    //创建Layer对象－－stage
    //Layer不会随着屏幕适配进行缩放。如何解决？？
    
    auto bkground = Sprite::create("background.png");
    bkground->setPosition(Point(WinSize.width/2.0, WinSize.height/2.0));
    this->addChild(bkground, ZORDER_BACKGROUND);
    
    //auto stage = Stage::create();
    auto stage = Stage::creatWithLevel(level);
    
    this->setstage(stage);
    this->addChild(stage, ZORDER_STAGE);

    //创建单点按键监听事件
    auto TouchEvent = EventListenerTouchOneByOne::create();
    
    //callback函数定义
    TouchEvent->onTouchBegan =
    [this](Touch* touch, Event* event)
    {
        this->setIsTouch(true);
        
        return true;
    };
    
    TouchEvent->onTouchMoved =
    [this](Touch* touch,Event* event)
    {
        this->setIsTouch(false);
    };
    
    TouchEvent->onTouchEnded =
    [this](Touch* touch,Event* event)
    {
        this->setIsTouch(false);
    };
    
    //EventDispatcher事件发报机中添加监听事件
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(TouchEvent, this);
    
    //创建物理碰撞监视器
    auto physicsContact = EventListenerPhysicsContact::create();
    
    //最初的碰撞
    physicsContact->onContactBegin =
    [this](PhysicsContact& contact)
    {
        
        auto bitmaskA = contact.getShapeA()->getCategoryBitmask();
        auto bitmaskB = contact.getShapeB()->getCategoryBitmask();
        
        if (( bitmaskA == static_cast<int>(Stage::TileType::Enemy) )||
            ( bitmaskB == static_cast<int>(Stage::TileType::Enemy) ))
        {
            this->GameFail();
        }
        return true;
    };
    
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(physicsContact, this);
    
    this->scheduleUpdate();
    
    return true;
}

//Updata函数
void MainScene::update(float dt)
{
    if (this->getIsTouch())
    {
        //MainScene中有一个stage容器，存放了stage对象
        //stage类里有一个player容器，存放了player对象
        //给player对象施加浮力参数的瞬间冲量
        _stage->getplayer()->getPhysicsBody()->applyImpulse(PHYSICS_ENGINE_IMPLUSE);
        
    }
}

void MainScene::GameFail()
{
    //
    _stage->getplayer()->removeFromParent();
    //getPhysicsBody()->setDynamic(false);
    
    auto winSize = Director::getInstance()->getWinSize();
    
    auto menulayer =LayerColor::create(Color4B(0,0,0,100));
    //LayerColor::initWithColor(Color4B(0,0,0,100));
    //create();
    
    auto gameover = Sprite::create("gameover.png");
    gameover->setPosition(Point(winSize.width/2.0, winSize.height/1.5));
    menulayer->addChild(gameover);
    
    auto menuItem = MenuItemImage::create("replay.png",
                                          "replay_pressed.png",
                                          [this](Ref* ref)
                                          {
                                              auto scene = MainScene::createWithLevel(_stage->getlevel());
                                              auto replay = TransitionMoveInT::create(1.0f, scene);
                                              Director::getInstance()->replaceScene(replay);
                                          });
    auto menu = Menu::create(menuItem, nullptr);
    
    menu->setPosition(Point(winSize.width/2.0, winSize.height/3));
    
    menulayer->addChild(menu);
    
    this->addChild(menulayer, ZORDER_MENU);

}
