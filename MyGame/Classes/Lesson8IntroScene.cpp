
#include "Lesson8IntroScene.h"
#include "ui/CocosGUI.h"
#include "Lesson8GameScene.h"

USING_NS_CC;

Scene* Lesson8IntroScene::createScene()
{
    return Lesson8IntroScene::create();
}

// on "init" you need to initialize your instance
bool Lesson8IntroScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // Init mouse listener
    auto mouseListener = EventListenerMouse::create();
    mouseListener->onMouseDown = CC_CALLBACK_1(Lesson8IntroScene::onMouseDown, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

    this->initUI();

    //SpriteBatchNode* spriteBatchNode = SpriteBatchNode::create("sprites.png");
    /*std::thread t([=]() {
        Director::getInstance()->getTextureCache()->addImageAsync("img5mb.jpg", CC_CALLBACK_1(Lesson8IntroScene::allTexturesLoaded, this));
        log("startLoading");
    });*/
    //t.detach();
    
    this->cache = SpriteFrameCache::getInstance();
    log("start loading img30mb.jpg");
    Director::getInstance()->getTextureCache()->addImageAsync("img30mb.jpg", [&](Texture2D* texture) {
        this->loadingBar->setPercent(50);
        log("start loading img30mb2.jpg");
        Director::getInstance()->getTextureCache()->addImageAsync("img30mb2.jpg", 
            CC_CALLBACK_1(Lesson8IntroScene::allTexturesLoaded, this));
    });
    
    // Loading Bar Background
    auto loadingBarBG = Sprite::create("loadingBarBG.png");
    loadingBarBG->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.3));
    addChild(loadingBarBG);
    //Loading Bar
    this->loadingBar = ui::LoadingBar::create("loadingBar.png");
    loadingBar->setPosition(loadingBarBG->getPosition());
    loadingBar->setDirection(ui::LoadingBar::Direction::LEFT);
    loadingBar->setPercent(10);
    this->addChild(loadingBar);

    /*this->schedule([=](float delta) {
        float percent = loadingBar->getPercent();
        percent++;
        loadingBar->setPercent(percent);
        if (percent >= 100) {
            this->unschedule("updateLoadingBar");
        }
    }, 0.3, "updateLoadingBar");*/


    /*auto sprite = Sprite::create("player.png");
    addChild(sprite);
    sprite->runAction(MoveBy::create(10, Vec2(800, 600)));*/

    //this->scheduleUpdate();
    return true;
}


//void Lesson8IntroScene::update(float dt) {
//    // Handle update game state here
//}


void Lesson8IntroScene::initUI() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // Menu
    Vector<MenuItem*> menuItems = {

        MenuItemLabel::create(  Label::createWithSystemFont("Settings", "Arial", 20)  , [&](Ref* sender) {
            CCLOG("Settings");
        }),
        MenuItemLabel::create(Label::createWithSystemFont("Quit", "Arial", 20), [&](Ref* sender) {
            CCLOG("Quit");
        }),
        MenuItemImage::create("button-normal.png", "button-selected.png", [&](Ref* sender) {
            /*auto node = dynamic_cast<Node*>(sender);
            node->getTag();*/
            CCLOG("Play Game");
        }),
    };

    auto menu = Menu::createWithArray(menuItems);
    addChild(menu);
    menu->alignItemsVertically();
    menu->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
}

void Lesson8IntroScene::onMouseDown(Event* event) {
    auto gameScene = Lesson8GameScene::createScene();

    // Replace scene
    Director::getInstance()->replaceScene(gameScene);







    // Transition scene with effect
    //Director::getInstance()->replaceScene(TransitionFade::create(0.5, gameScene));





    //Director::getInstance()->replaceScene(TransitionFade::create(1, gameScene, Color3B(255, 255, 255)));


    //Director::getInstance()->replaceScene(TransitionFlipX::create(1, gameScene));


    //Director::getInstance()->replaceScene(TransitionSlideInT::create(0.5, gameScene));


    //Director::getInstance()->pushScene(gameScene);
   
}

void Lesson8IntroScene::allTexturesLoaded(Texture2D* texture) {
    this->loadingBar->setPercent(100);
    log("all loaded");

    this->mySprite = Sprite::create("img30mb2.jpg");
    this->mySprite->setPosition(200, 200);
    addChild(this->mySprite);
}

