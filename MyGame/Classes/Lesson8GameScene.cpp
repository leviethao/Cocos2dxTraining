
#include "Lesson8GameScene.h"
#include "ui/CocosGUI.h"
#include "Lesson8ClosingScene.h"

USING_NS_CC;

Scene* Lesson8GameScene::createScene()
{
    return Lesson8GameScene::create();
}

// on "init" you need to initialize your instance
bool Lesson8GameScene::init()
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
    mouseListener->onMouseDown = CC_CALLBACK_1(Lesson8GameScene::onMouseDown, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

    this->initUI();

    //this->scheduleUpdate();
    return true;
}


//void Lesson8GameScene::update(float dt) {
//    // Handle update game state here
//}


void Lesson8GameScene::initUI() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto label = Label::createWithTTF("Game Scene", "fonts/Marker Felt.ttf", 20);
    addChild(label);
    label->setPosition(visibleSize / 2);


    // Show hide a Node
    this->schedule([=](float delta) {
        label->setVisible(!label->isVisible());

        /*Node* node = Node::create();
        node->addChild(label);
        node->addChild(menu);
        node->addChild(sprite);
        node->setPosition();
        node->setVisible();*/

        // Exit game
        //Director::getInstance()->end();

    }, 1, "sche1");
}

void Lesson8GameScene::onMouseDown(Event* event) {

    auto closingScene = Lesson8ClosingScene::createScene(99);
    Director::getInstance()->replaceScene(closingScene);


    //Director::getInstance()->popScene();
}

