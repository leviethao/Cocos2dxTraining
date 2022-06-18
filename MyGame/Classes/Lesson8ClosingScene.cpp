
#include "Lesson8ClosingScene.h"
#include "ui/CocosGUI.h"
#include <cstring>

USING_NS_CC;

int score = 0;

Scene* Lesson8ClosingScene::createScene(int _score)
{
    score = _score;
    return Lesson8ClosingScene::create();
}

// on "init" you need to initialize your instance
bool Lesson8ClosingScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    this->initUI();

    //this->scheduleUpdate();
    return true;
}


//void Lesson8ClosingScene::update(float dt) {
//    // Handle update game state here
//}


void Lesson8ClosingScene::initUI() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    std::string str = "Closing Scene. Score: " + std::to_string(score);

    auto label = Label::createWithTTF(str, "fonts/Marker Felt.ttf", 20);
    addChild(label);
    label->setPosition(visibleSize / 2);
}