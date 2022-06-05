
#include "Lesson4.h"

USING_NS_CC;

Scene* Lesson4::createScene()
{
    return Lesson4::create();
}

// on "init" you need to initialize your instance
bool Lesson4::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // Init for move sprite
    this->mouseLoc = Vec2::ZERO;
    this->direction = Vec2(1, 1);
    this->speed = 200;

    this->mySprite = Sprite::create("player.png");
    addChild(this->mySprite);
    this->mySprite->setPosition(Vec2(50, 50));

    // Init mouse event listener
    auto mouseListener = EventListenerMouse::create();
    mouseListener->onMouseDown = CC_CALLBACK_1(Lesson4::onMouseDown, this);
    mouseListener->onMouseMove = CC_CALLBACK_1(Lesson4::onMouseMove, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

    this->scheduleUpdate();
    return true;
}


void Lesson4::update(float dt) {
    // Handle update game state here

    Vec2 curPos = this->mySprite->getPosition();
    Vec2 deltaMove = this->mouseLoc - curPos;
    if (abs(deltaMove.x) > 5 && abs(deltaMove.y) > 5) {
        Vec2 newPos = curPos + this->speed * dt * this->direction;
        this->mySprite->setPosition(newPos);
    }
}

void Lesson4::onMouseDown(Event* event) {
    EventMouse* e = (EventMouse*)event;

    Vec2 location = e->getLocationInView();
    CCLOG("Mouse down location: (%f, %f)", location.x, location.y);

    //this->mySprite->setPosition(Vec2(location.x, location.y));
    auto moveTo = MoveTo::create(1, location);
    this->mySprite->stopAllActions();
    this->mySprite->runAction(moveTo);
    auto mouseButton = e->getMouseButton();
    switch (mouseButton) {
    case EventMouse::MouseButton::BUTTON_LEFT:
        CCLOG("Mouse left clicked");
        break;
    case EventMouse::MouseButton::BUTTON_RIGHT:
        CCLOG("Mouse right clicked");
        break;
    case EventMouse::MouseButton::BUTTON_MIDDLE:
        CCLOG("Mouse middle clicked");
        break;
    default: 
        break;
    }
}

void Lesson4::onMouseMove(Event* event) {
    EventMouse* e = (EventMouse*)event;

    Vec2 location = e->getLocationInView();
    //CCLOG("Mouse move location: (%f, %f)", location.x, location.y);*/

    //this->mySprite->setPosition(location);

    /*auto moveTo = MoveTo::create(1, location);
    this->mySprite->stopAllActions();
    this->mySprite->runAction(moveTo);*/

    // 
    this->mouseLoc = location;
    this->direction = location - this->mySprite->getPosition();
    this->direction.normalize();
}