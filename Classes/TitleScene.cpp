#include "TitleScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

const int INITALZE_LEVEL = 1;

TitleScene::TitleScene()
{
    
}

TitleScene::~TitleScene()
{
    
}

Scene* TitleScene::createScene()
{
    auto scene = Scene::create();
    
    auto layer = TitleScene::create();
    
    scene->addChild(layer);
    
    return scene;
    
}

bool TitleScene::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    auto winSize = Director::getInstance()->getWinSize();
    
    auto bk = Sprite::create("title.png");
    bk->setPosition(Vec2(winSize.width/2.0, winSize.height/2.0));
    this->addChild(bk);
    
    auto startmenu = MenuItemImage::create("start.png",
                                           "start_pressed.png",
                                           [this](Ref* ref)
                                           {
                                               auto scene = MainScene::createWithLevel(INITALZE_LEVEL);
                                               auto chg   = TransitionFade::create(1.0f, scene);
                                               Director::getInstance()->replaceScene(chg);
                                           });
    
    auto menu = Menu::createWithItem(startmenu);
    menu->setPosition(Point(winSize.width/1.5, winSize.height/3));
    
    this->addChild(menu);
    
    return true;
}

void TitleScene::update(float dt)
{

}

void TitleScene::onEnterTransitionDidFinish()
{
    Layer::onEnterTransitionDidFinish();
   
#ifndef __MUTE_ON__
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("title.caf", true);
    CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.5);
#endif
    
}
