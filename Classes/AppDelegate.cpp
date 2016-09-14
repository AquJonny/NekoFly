#include "AppDelegate.h"
#include "HelloWorldScene.h"

USING_NS_CC;

//������Ļ�ֱ������� ���� or ����
#define Landscape

#ifdef Landscape

//Landscape
//default=Retina

static cocos2d::Size iPhon4DesignSize = cocos2d::Size(480, 320);		//3 : 2 320 ���� x 480 ���� Point(320*480)
static cocos2d::Size iPhon5DesignSize = cocos2d::Size(568, 320);		//16: 9 640 ���� x 1136���� Point(320*568)
static cocos2d::Size iPhon6DesignSize = cocos2d::Size(736, 414);		//16: 9 1080���� x 1920���� Point(375*667,414*736)

static cocos2d::Size iPhon4FrameSize = cocos2d::Size(480, 320);			//3 : 2 320 ���� x 480 ���� Point(320*480)
static cocos2d::Size iPhon5FrameSize = cocos2d::Size(1136, 640);		//16: 9 640 ���� x 1136���� Point(320*568)
static cocos2d::Size iPhon6FrameSize = cocos2d::Size(1920, 1080);		//16: 9 1080���� x 1920���� Point(375*667,414*736)
#else //if (ResolutionType == Portait)

//Portait
//default=Retina

static cocos2d::Size iPhon4DesignSize = cocos2d::Size(480, 320);		//3 : 2 320 ���� x 480 ���� Point(320*480)
static cocos2d::Size iPhon5DesignSize = cocos2d::Size(568, 320);		//16: 9 640 ���� x 1136���� Point(320*568)
static cocos2d::Size iPhon6DesignSize = cocos2d::Size(736, 414);		//16: 9 1080���� x 1920���� Point(375*667,414*736)

static cocos2d::Size iPhon4FrameSize = cocos2d::Size(320, 480);			//3 : 2 320 ���� x 480 ���� Point(320*480)
static cocos2d::Size iPhon5FrameSize = cocos2d::Size(640, 1136);		//16: 9 640 ���� x 1136���� Point(320*568)
static cocos2d::Size iPhon6FrameSize = cocos2d::Size(1080, 1920);		//16: 9 1080���� x 1920���� Point(375*667,414*736)
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
		//���Զ�����ʱ����Ҫ������Ϸ����.�ڶ�������������Ϸ����λ�����С
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        glview = GLViewImpl::createWithRect("MyCppGame", cocos2d::Rect(0, 0, designResolutionSize.width, designResolutionSize.height));
#else
		//�ƶ�������ʱ��Ĭ����Ϸ���ھ����豸��ʾ��С�����Բ���Ҫ�������ô��ڴ�С
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
	
	//ȡ���豸������ ����ԴCCPlatformConfig.h
	//CC_TARGET_PLATFORM
	//#define CC_PLATFORM_UNKNOWN            0
	//#define CC_PLATFORM_IOS                1 ��iPhone
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

	//ȡ���豸��������CC_TARGET_PLATFORMͬ��Ч�� ����ԴCCApplicationProtocol.h
	auto platform = Appliction::getInstance()->getTargetPlantform();
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

	//�豸�����Ļ��������:
	//����cocos2dx�е���ʾ�ߴ�,��4��(or����?)�������
	//��Դ�ߴ�(ResourceSize):
	//���米��ͼ�ķֱ���,��ͼ�ķֱ��� �������Լ���Resource����
	//
	//��Ƴߴ�(DesignSize / WinSize):
	//��Ƶ���ʾ���ڵķֱ���          ���Լ��趨,һ����Resource,�豸�ֱ���,�豸��ʾ�����йء�
	//                                           �趨��,���������ֵ������Ϸ������ϵ��
	//
	//�豸�ߴ�(FrameSize):
	//�޷����������ʵ���豸�Ĳ�������,ͨ��glview->getFrameSize()�������
	//
	//��Դ����Ƴߴ�֮�������:
	//ͨ��director->setContentScaleFactor(float x)�����趨
	//director->setContentScaleFactor(MIN(��Դ.height/���.height, ��Դ.width/���.width))
	//�������趨����
	//��ƺ��豸�ߴ�֮�������:
	//ͨ��glview->setDesignResolutionSize(float x,float y,ResolutionPolicy)�����趨
	//glview->setDesignResolutionSize(���.width, ���.height, ��䷽ʽ)
	//�������趨����
	//������䷽ʽ:
	//1��EXACT_FIT ������Ϸ���ݶ�������Ļ�ڿɼ������Ҳ����ṩ����ϵ����x,y�ᱻ���죬ʹ����������Ļ�����Կ��ܻ�����α䣬���е�Ӧ�ó����������ܻ����������ѹ���ġ�
	//2��NO_BORDER һ������������Ļ������һ�����򳬳���Ļ��������Σ����ǿ�����һЩ�ü���
	//3��SHOW_ALL ��ģʽ�ᾡ���ܰ�ԭʼ��߱ȷŴ���Ϸ���磬ͬʱʹ����Ϸ����ȫ���ɼ������ݲ����α䣬�������ܻ���������ڱߣ�����Ļ�л������ס�
	//4��FIXED_WIDTH ��ģʽ�����Ŵ���Ϸ�����ڵ���������Ӧ��Ļ�Ŀ�ȣ�����ԭʼ��߱ȷŴ�
	//5��FIXED_HEIGHT ����һ��ģʽ�෴��
	//
	//���������˼·
	//1.ȷ���豸��ʵ�ʳߴ������豸����ʾ��(4:3?16:9)
	//2.�����豸����ʾ���������Ӧ����Ƴߴ�
	//3.������Ƴߴ�(��ʾ��)׼����Ӧ��Resource
	//�����ڸ���ͷǸ��������,������Ҫ׼��2����Դ�ֱ��Ӧ
	//��ʹ�÷Ǹ������Դ���Խ�Լ�ڴ�ռ��ʹ��.
	//
	//����:
	//���ͨ��ʵ�ʳߴ�����ʾ�Ȳ��������Ƴߴ�
	//
	//iOS �豸���еķֱ������£�
	//iPhone/iPod Touch
	//3 :2 ��ͨ   �� 320 ���� x 480 ���� Point(320*480)iPhone 1��3G��3GS��iPod Touch 1��2��3
	//3 :2 Retina �� 640 ���� x 960 ���� Point(320*480)iPhone 4��4S��iPod Touch 4
	//16:9 Retina �� 640 ���� x 1136���� Point(320*568)iPhone 5��5s��SE��iPod Touch 5
	//16:9 Retina �� 750 ���� x 1334���� Point(320*568,375*667)iPhone 6
	//16:9 Retina �� 1080���� x 1920���� Point(375*667,414*736)iPhone 6
	//
	//iPad
	//4 :3 Retina �� 1536���� x 2048���� Point(768*1024)iPad��iPad mini��iPad air
	//4 :3 Retina �� 2048���� x 2732���� Point(1024*1366)iPad Pro
	//
	//Ϊ�˷��㿪����Ա������iOS ��ͳһʹ�õ㣨Point���Խ���Ԫ�صĴ�С����������
	//������صĻ����ϵ���£�
	//��ͨ   �� 1�� = 1���� 
	//Retina �� 1�� = 2���� 
	//
	//���� iPhone 5 �� iPod Touch 5 �Ļ����ϣ����ڿ�������˵��
	//���Ľ����С���� 320 x 568�㣬��ֻ����������Сȥ������Ľ��档
	//���磺����һ����ť��Ҫ������Ļ�м��λ�ã�
	//��ô�ڽ����СΪ 320 x 480�� ���豸�ϣ�ֻ���������� center Ϊ (320/2, 480/2) λ�ü��ɣ�
	//�� 3��2 Retina ����ϵͳ�����ťҲ������ȷ����ʾ���м䣻
	//������Ļ��СΪ 320 x 568�� ���豸�ϣ������������ center Ϊ (320/2, 568/2)��
	//
	//https://designcode.io/iosdesign-guidelines
	//https://www.paintcodeapp.com/news/ultimate-guide-to-iphone-resolutions
	
	auto frameSize = glview->getFrameSize();

	//�����ļ��������ļ����б�
	std::vector<std::string> serchResolutionOrder;

	switch( platform )
	{
		case Platform::OS_IPHONE:
		case Platform::OS_IPAD:
			//���ݷֱ���(�߿��)�趨DesignSize(WinSize)
			//���ݷֱ���(�߿��)�趨ʹ�õ���Դ·��Retina��NonRetina
#ifdef Landscape
			if( frameSize.width > iPhon5FrameSize.width )
#else
			if( frameSize.height > iPhon5FrameSize.height )
#endif
			{
				director->setContentScaleFactor(2.0f);
				
				glview->setDesignResolutionSize(iPhon6FrameSize.width, iPhon6FrameSize.height, ResolutionPolicy:FIXED_HEIGHT);
				
				serchResolutionOrder.push_back("images/retina");
			}
#ifdef Landscape
			else if( frameSize.width > iPhon4DesignSize.width )
#else
			else if( frameSize.height > iPhon4DesignSize.height )
#endif			
			{
				director->setContentScaleFactor(2.0f);
				
				glview->setDesignResolutionSize(iPhon5FrameSize.width, iPhon5FrameSize.height, ResolutionPolicy:FIXED_HEIGHT);
				
				serchResolutionOrder.push_back("images/retina");
			}
			else
			{
				director->setContentScaleFactor(1.0f);
				
				glview->setDesignResolutionSize(iPhon4FrameSize.width, iPhon4FrameSize.height, ResolutionPolicy:FIXED_HEIGHT);

				serchResolutionOrder.push_back("images/nonretina");
			}

			//iOS֧�ֵ���Ƶ��ʽ
			serchResolutionOrder.push_back("music/caf");
			serchResolutionOrder.push_back("se/caf");
		break;
		
		case Platform::ANDROID:
			//Android��ʱ������,�̶�ΪiPhone4�趨
			director->setContentScaleFactor(1.0f);
			
			glview->setDesignResolutionSize(iPhon4FrameSize.width, iPhon4FrameSize.height, ResolutionPolicy:FIXED_HEIGHT);

			serchResolutionOrder.push_back("images/nonretina");

			//Android֧�ֵ���Ƶ��ʽ
			serchResolutionOrder.push_back("music/ogg");
			serchResolutionOrder.push_back("se/ogg");
		break;
		
		default:
			//����ƽ̨���趨
		break;
		
	}

	serchResolutionOrder.push_back("fonts");
	serchResolutionOrder.push_back("map");
	serchResolutionOrder.push_back("model");
	serchResolutionOrder.push_back("psd");

	FileUtils::getInstance()->setSerchiResolutionOrder(serchResolutionOrder);
	

    register_all_packages();

    // create a scene. it's an autorelease object
    auto scene = HelloWorld::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. Note, when receiving a phone call it is invoked.
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be paused
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
