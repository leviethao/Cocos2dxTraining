#include "MainMenuScene.h"
#include "AudioEngine.h"
#include "GameScene.h"

USING_NS_CC;

Scene* MainMenuScene::createScene()
{
    return MainMenuScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in GameScene.cpp\n");
}

// on "init" you need to initialize your instance
bool MainMenuScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    AudioEngine::preload("sounds/background.mp3", [&](bool isSuccess) {
        log("Preload background.pm3 %s", isSuccess ? "Success" : "Failed");
        if (isSuccess) {
            this->backgroundMusic = AudioEngine::play2d("sounds/background.mp3", true);
        }
    });

    this->soundLabel = Label::createWithSystemFont(std::string("Sound: ") + std::string(this->soundOn ? "ON" : "OFF"), "Arial", 20);

    Vector<MenuItem*> menuItems = {
        MenuItemLabel::create(Label::createWithSystemFont("Play", "Arial", 20)  , [=](Ref* sender) {
            auto gameScene = GameScene::create();
            Director::getInstance()->replaceScene(gameScene);
        }),
        MenuItemLabel::create(this->soundLabel, [&](Ref* sender) {
            this->soundOn = !this->soundOn;
            this->soundLabel->setString(std::string("Sound: ") + std::string(this->soundOn ? "ON" : "OFF"));
        }),
        MenuItemLabel::create(Label::createWithSystemFont("Quit", "Arial", 20)  , [=](Ref* sender) {
            Director::getInstance()->end();
        }),
    };
    
    auto menu = Menu::createWithArray(menuItems);
    addChild(menu);
    menu->alignItemsVertically();
    menu->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));

    return true;
}

