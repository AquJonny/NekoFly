#include "AppDelegate.h"
#include "TitleScene.h"

USING_NS_CC;

const int INITALZE_LEVEL = 1;

//定义屏幕分辨率类型 横屏 or 竖屏
#define Landscape

#ifdef Landscape

//Landscape
//default=Retina

static cocos2d::Size iPhon4DesignSize = cocos2d::Size(480, 320);		//3 : 2 320 像素 x 480 像素 Point(320*480)
static cocos2d::Size iPhon5DesignSize = cocos2d::Size(568, 320);		//16: 9 640 像素 x 1136像素 Point(320*568)
static cocos2d::Size iPhon6DesignSize = cocos2d::Size(736, 414);		//16: 9 1080像素 x 1920像素 Point(375*667,414*736)

static cocos2d::Size iPhon4FrameSize = cocos2d::Size(960, 640);			//3 : 2 320 像素 x 480 像素 Point(320*480)
static cocos2d::Size iPhon5FrameSize = cocos2d::Size(1136, 640);		//16: 9 640 像素 x 1136像素 Point(320*568)
static cocos2d::Size iPhon6FrameSize = cocos2d::Size(1920, 1080);		//16: 9 1080像素 x 1920像素 Point(375*667,414*736)
#else //if (ResolutionType == Portait)

//Portait
//default=Retina

static cocos2d::Size iPhon4DesignSize = cocos2d::Size(320, 480);		//3 : 2 320 像素 x 480 像素 Point(320*480)
static cocos2d::Size iPhon5DesignSize = cocos2d::Size(320, 568);		//16: 9 640 像素 x 1136像素 Point(320*568)
static cocos2d::Size iPhon6DesignSize = cocos2d::Size(414, 736);		//16: 9 1080像素 x 1920像素 Point(375*667,414*736)

static cocos2d::Size iPhon4FrameSize = cocos2d::Size(640, 960);			//3 : 2 320 像素 x 480 像素 Point(320*480)
static cocos2d::Size iPhon5FrameSize = cocos2d::Size(640, 1136);		//16: 9 640 像素 x 1136像素 Point(320*568)
static cocos2d::Size iPhon6FrameSize = cocos2d::Size(1080, 1920);		//16: 9 1080像素 x 1920像素 Point(375*667,414*736)
#endif



AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
}

// if you want a different context, modify the value of glContextAttrs
// it will affect all platforms
void AppDelegate::initGLContextAttrs()
{
    // set OpenGL context attributes: red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};
    
    GLView::setGLContextAttrs(glContextAttrs);
}

// if you want to use the package manager to install more packages,
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        //电脑端运行时候需要创建游戏窗口.第二个参数就是游戏窗口位置与大小
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        glview = GLViewImpl::createWithRect("MyCppGame", cocos2d::Rect(0, 0, iPhon6DesignSize.width, iPhon6DesignSize.height));
#else
        //移动端运行时候默认游戏窗口就是设备显示大小，所以不需要另外设置窗口大小
        glview = GLViewImpl::create("MyCppGame");
#endif
        director->setOpenGLView(glview);
    }
    
    // turn on display FPS
    director->setDisplayStats(false);
    
    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0f / 60);
    
    // Set the design resolution
    //glview->setDesignResolutionSize(designResolutionSize.width,
    //								designResolutionSize.height,
    //								ResolutionPolicy::NO_BORDER);
    
    //取得设备的类型 ※来源CCPlatformConfig.h
    //CC_TARGET_PLATFORM
    //#define CC_PLATFORM_UNKNOWN            0
    //#define CC_PLATFORM_IOS                1 ※iPhone
    //#define CC_PLATFORM_ANDROID            2
    //#define CC_PLATFORM_WIN32              3
    //#define CC_PLATFORM_MARMALADE          4
    //#define CC_PLATFORM_LINUX              5
    //#define CC_PLATFORM_BADA               6
    //#define CC_PLATFORM_BLACKBERRY         7
    //#define CC_PLATFORM_MAC                8
    //#define CC_PLATFORM_NACL               9
    //#define CC_PLATFORM_EMSCRIPTEN        10
    //#define CC_PLATFORM_TIZEN             11
    //#define CC_PLATFORM_QT5               12
    //#define CC_PLATFORM_WINRT             13
    
    //取得设备的类型与CC_TARGET_PLATFORM同样效果 ※来源CCApplicationProtocol.h
    auto platform = Application::getInstance()->getTargetPlatform();
    //enum class Platform
    //{
    //    OS_WINDOWS,     /**< Windows */
    //    OS_LINUX,       /**< Linux */
    //    OS_MAC,         /**< Mac OS X*/
    //    OS_ANDROID,     /**< Android */
    //    OS_IPHONE,      /**< iPhone */
    //    OS_IPAD,        /**< iPad */
    //    OS_BLACKBERRY,  /**< BlackBerry */
    //    OS_NACL,        /**< Native Client in Chrome */
    //    OS_EMSCRIPTEN,  /**< Emscripten */
    //    OS_TIZEN,       /**< Tizen */
    //    OS_WINRT,       /**< Windows Runtime Applications */
    //    OS_WP8          /**< Windows Phone 8 Applications */
    //};
    
    //设备别的屏幕适配问题:
    //对于cocos2dx中的显示尺寸,有4个(or更多?)相关数据
    //资源尺寸(ResourceSize):
    //例如背景图的分辨率,贴图的分辨率 ※根据自己的Resource设置
    //
    //设计尺寸(DesignSize / WinSize):
    //设计的显示窗口的分辨率          ※自己设定,一般与Resource,设备分辨率,设备显示比例有关★
    //                                           设定后,根据这个数值创建游戏内坐标系★
    //
    //设备尺寸(FrameSize):
    //无法变更，根据实际设备的参数决定,通过glview->getFrameSize()方法获得
    //
    //资源与设计尺寸之间的缩放:
    //通过director->setContentScaleFactor(float x)方法设定
    //director->setContentScaleFactor(MIN(资源.height/设计.height, 资源.width/设计.width))
    //↑常用设定方法
    //设计和设备尺寸之间的缩放:
    //通过glview->setDesignResolutionSize(float x,float y,ResolutionPolicy)方法设定
    //glview->setDesignResolutionSize(设计.width, 设计.height, 填充方式)
    //↑常用设定方法
    //关于填充方式:
    //1）EXACT_FIT 整个游戏内容都会在屏幕内可见，并且不用提供比例系数。x,y会被拉伸，使内容铺满屏幕，所以可能会出现形变，所有的应用程序看起来可能会是拉伸或者压缩的。
    //2）NO_BORDER 一个方向铺满屏幕，另外一个方向超出屏幕，不会变形，但是可能有一些裁剪。
    //3）SHOW_ALL 该模式会尽可能按原始宽高比放大游戏世界，同时使得游戏内容全部可见。内容不会形变，不过可能会出现两条黑边，即屏幕中会有留白。
    //4）FIXED_WIDTH 该模式会横向放大游戏世界内的内容以适应屏幕的宽度，纵向按原始宽高比放大。
    //5）FIXED_HEIGHT 与上一中模式相反。
    //
    //基本的设计思路
    //1.确定设备的实际尺寸→获得设备的显示比(4:3?16:9)
    //2.根据设备的显示比例设计相应的设计尺寸
    //3.根据设计尺寸(显示比)准备相应的Resource
    //※由于高清和非高清的区别,可能需要准备2套资源分别对应
    //※使用非高清的资源可以节约内存空间的使用.
    //
    //课题:
    //如何通过实际尺寸获得显示比并且设计设计尺寸
    //
    //iOS 设备现有的分辨率如下：
    //iPhone/iPod Touch
    //3 :2 普通   屏 320 像素 x 480 像素 Point(320*480)iPhone 1、3G、3GS，iPod Touch 1、2、3
    //3 :2 Retina 屏 640 像素 x 960 像素 Point(320*480)iPhone 4、4S，iPod Touch 4
    //16:9 Retina 屏 640 像素 x 1136像素 Point(320*568)iPhone 5、5s、SE，iPod Touch 5
    //16:9 Retina 屏 750 像素 x 1334像素 Point(320*568,375*667)iPhone 6
    //16:9 Retina 屏 1080像素 x 1920像素 Point(375*667,414*736)iPhone 6
    //
    //iPad
    //4 :3 Retina 屏 1536像素 x 2048像素 Point(768*1024)iPad，iPad mini，iPad air
    //4 :3 Retina 屏 2048像素 x 2732像素 Point(1024*1366)iPad Pro
    //
    //为了方便开发人员开发，iOS 中统一使用点（Point）对界面元素的大小进行描述。
    //点跟像素的换算关系如下：
    //普通   屏 1点 = 1像素
    //Retina 屏 1点 = 2像素
    //
    //而在 iPhone 5 跟 iPod Touch 5 的机器上，对于开发者来说，
    //它的界面大小就是 320 x 568点，你只需根据这个大小去调整你的界面。
    //比如：我有一个按钮，要放在屏幕中间的位置，
    //那么在界面大小为 320 x 480点 的设备上，只需设置它的 center 为 (320/2, 480/2) 位置即可，
    //在 3：2 Retina 屏上系统这个按钮也可以正确的显示在中间；
    //而在屏幕大小为 320 x 568点 的设备上，你就设置它的 center 为 (320/2, 568/2)。
    //
    //https://designcode.io/iosdesign-guidelines
    //https://www.paintcodeapp.com/news/ultimate-guide-to-iphone-resolutions
    
    auto frameSize = glview->getFrameSize();
    
    //创建文件检索用文件夹列表
    std::vector<std::string> searchResolutionOrder;
    
    switch( platform )
    {
        case Platform::OS_IPHONE:
        case Platform::OS_IPAD:
            //根据分辨率(高宽比)设定DesignSize(WinSize)
            //根据分辨率(高宽比)设定使用的资源路径Retina与NonRetina
#ifdef Landscape
            if( frameSize.width > iPhon5FrameSize.width )
#else
                if( frameSize.height > iPhon5FrameSize.height )
#endif
                {
                    director->setContentScaleFactor(2.0f);
                    
                    glview->setDesignResolutionSize(iPhon6DesignSize.width, iPhon6DesignSize.height, ResolutionPolicy::FIXED_HEIGHT);
                    
                    searchResolutionOrder.push_back("images/retina");
                }
#ifdef Landscape
                else if( frameSize.width > iPhon4FrameSize.width )
#else
                    else if( frameSize.height > iPhon4FrameSize.height )
#endif
                    {
                        director->setContentScaleFactor(2.0f);
                        
                        glview->setDesignResolutionSize(iPhon5DesignSize.width, iPhon5DesignSize.height, ResolutionPolicy::FIXED_HEIGHT);
                        
                        searchResolutionOrder.push_back("images/retina");
                    }
                    else
                    {
                        director->setContentScaleFactor(1.0f);
                        
                        glview->setDesignResolutionSize(iPhon4DesignSize.width, iPhon4DesignSize.height, ResolutionPolicy::FIXED_HEIGHT);
                        
                        searchResolutionOrder.push_back("images/nonretina");
                    }
            
            //iOS支持的音频格式
            searchResolutionOrder.push_back("music/caf");
            searchResolutionOrder.push_back("se/caf");
            break;
            
        case Platform::OS_ANDROID:
            //Android暂时不考虑,固定为iPhone4设定
            director->setContentScaleFactor(1.0f);
            
            glview->setDesignResolutionSize(iPhon4DesignSize.width, iPhon4DesignSize.height, ResolutionPolicy::FIXED_HEIGHT);
            
            searchResolutionOrder.push_back("images/nonretina");
            
            //Android支持的音频格式
            searchResolutionOrder.push_back("music/ogg");
            searchResolutionOrder.push_back("se/ogg");
            break;
            
        default:
            //其他平台的设定
            break;
            
    }
    
    searchResolutionOrder.push_back("fonts");
    searchResolutionOrder.push_back("map");
    searchResolutionOrder.push_back("model");
    searchResolutionOrder.push_back("psd");
    
    FileUtils::getInstance()->setSearchResolutionsOrder(searchResolutionOrder);
    
    register_all_packages();
    
    // create a scene. it's an autorelease object
    //auto scene = MainScene::createScene();
    auto scene = TitleScene::createScene();
    
    // run
    director->runWithScene(scene);
    
    //
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadbackgroundmusic("title.caf");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadbackgroundmusic("main.caf");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadbackgroundmusic("clears.caf");
    
    
    return true;
}

// This function will be called when the app is inactive. Note, when receiving a phone call it is invoked.
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();
    
    // if you use SimpleAudioEngine, it must be paused
    CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();
    
    // if you use SimpleAudioEngine, it must resume here
    CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
