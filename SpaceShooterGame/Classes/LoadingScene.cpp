#include "LoadingScene.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

Scene* LoadingScene::createScene()
{
    return LoadingScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in GameScene.cpp\n");
}

// on "init" you need to initialize your instance
bool LoadingScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    this->handleLoading();

    return true;
}

void LoadingScene::handleLoading() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // Loading Bar Background
    auto loadingBarBG = Sprite::create("loadingBarBG.png");
    loadingBarBG->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.3));
    addChild(loadingBarBG);
    //Loading Bar
    auto loadingBar = ui::LoadingBar::create("loadingBar.png");
    loadingBar->setPosition(loadingBarBG->getPosition());
    loadingBar->setDirection(ui::LoadingBar::Direction::LEFT);
    loadingBar->setPercent(10);
    this->addChild(loadingBar);

    this->schedule([=](float delta) {
        float percent = loadingBar->getPercent();
        percent++;
        loadingBar->setPercent(percent);
        if (percent >= 100) {
            this->unschedule("updateLoadingBar");
        }
    }, 0.05, "updateLoadingBar");
}

