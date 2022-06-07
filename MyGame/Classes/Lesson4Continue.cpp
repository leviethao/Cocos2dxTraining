
#include "Lesson4Continue.h"

USING_NS_CC;

Scene* Lesson4Continue::createScene()
{
    return Lesson4Continue::create();
}

// on "init" you need to initialize your instance
bool Lesson4Continue::init()
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
    this->mySprite->setPosition(Vec2(200, 200));

    this->mySprite2 = Sprite::create("player.png");
    addChild(this->mySprite2);
    this->mySprite2->setPosition(Vec2(300, 200));

    // Init mouse event listener
    auto mouseListener = EventListenerMouse::create();
    mouseListener->onMouseDown = CC_CALLBACK_1(Lesson4Continue::onMouseDown, this);
    mouseListener->onMouseUp = CC_CALLBACK_1(Lesson4Continue::onMouseUp, this);
    mouseListener->onMouseMove = CC_CALLBACK_1(Lesson4Continue::onMouseMove, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);


    // Init keyboard event listeners
    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = CC_CALLBACK_2(Lesson4Continue::onKeyPressed, this);
    listener->onKeyReleased = CC_CALLBACK_2(Lesson4Continue::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);


    // Init custom event listeners
    auto customListener = EventListenerCustom::create("custom_event1", [](EventCustom* event) {
        /*char* data = static_cast<char*>(event->getUserData());*/
        //CCLOG("data: %s", data);
        float* data = static_cast<float*>(event->getUserData());
        CCLOG("data: %f", *data);
    });
    _eventDispatcher->addEventListenerWithSceneGraphPriority(customListener, this);

    // Custom event
    /*this->mySprite->runAction(Sequence::create(MoveTo::create(2, Vec2(200, 200)), CallFunc::create([=]() {
        EventCustom customEvent1("custom_event1");
        float data = 3.14;
        customEvent1.setUserData(&data);
        _eventDispatcher->dispatchEvent(&customEvent1);
    }), nullptr));*/

    this->scheduleUpdate();
    return true;
}


void Lesson4Continue::update(float dt) {
    // Handle update game state here

    /*Vec2 curPos = this->mySprite->getPosition();
    Vec2 deltaMove = this->mouseLoc - curPos;
    if (abs(deltaMove.x) > 5 && abs(deltaMove.y) > 5) {
        Vec2 newPos = curPos + this->speed * dt * this->direction;
        this->mySprite->setPosition(newPos);
    }*/

    // move by key press
    if (this->isKeyDown) {
        Vec2 curPos = this->mySprite->getPosition();
        Vec2 newPos = curPos + (this->speed * dt * this->direction);
        this->mySprite->setPosition(newPos);
    }


    //handle collision
    // Vec2 r1 = Vec2(this->mySprite->getContentSize().width / 2, this->mySprite->getContentSize().height / 2);
    // Vec2 r2 = this->
    // Vec2 distanceCollision = this->mySprite->getContentSize().
}


void Lesson4Continue::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {
    CCLOG("Pressed keycode: %d", keyCode);
    // Move by key
    switch (keyCode) {
    case EventKeyboard::KeyCode::KEY_UP_ARROW:
        this->direction.y = 1;
        break;
    case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
        this->direction.y = -1;
        break;
    case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
        this->direction.x = -1;
        break;
    case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
        this->direction.x = 1;
        break;
    default:
        break;
    }

    this->isKeyDown = true;

    this->direction.normalize();
}


void Lesson4Continue::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {
    CCLOG("Released keyCode: %d", keyCode);

    // Stop move by key
    switch (keyCode) {
    case EventKeyboard::KeyCode::KEY_UP_ARROW:
        this->direction.y = 0;
        break;
    case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
        this->direction.y = 0;
        break;
    case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
        this->direction.x = 0;
        break;
    case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
        this->direction.x = 0;
        break;
    default:
        break;
    }

    this->isKeyDown = false;

    this->direction.normalize();
}

void Lesson4Continue::onMouseDown(Event* event) {
    EventMouse* e = (EventMouse*)event;

    Vec2 location = e->getLocationInView();
    /*CCLOG("Mouse down location: (%f, %f)", location.x, location.y);*/
    auto rect = this->mySprite->getBoundingBox();
    if (rect.containsPoint(location)) {
        CCLOG("Sprite location: (%f, %f)", this->mySprite->getPosition().x, this->mySprite->getPosition().y);
    }
    //this->mySprite->setPosition(Vec2(location.x, location.y));
    /*auto moveTo = MoveTo::create(1, location);
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
    }*/



    // Dragdrop
    if (rect.containsPoint(location)) {
        this->isDragDrop = true;
    }

    //9. Shooting
    //this->shootingBullet(location);
}


void Lesson4Continue::onMouseUp(Event* event) {
    EventMouse* e = (EventMouse*)event;

    Vec2 location = e->getLocationInView();
    /*CCLOG("Mouse down location: (%f, %f)", location.x, location.y);*/
   
    // Dragdrop
    this->isDragDrop = false;
}

void Lesson4Continue::onMouseMove(Event* event) {
    EventMouse* e = (EventMouse*)event;

    Vec2 location = e->getLocationInView();
    //CCLOG("Mouse move location: (%f, %f)", location.x, location.y);*/

    //this->mySprite->setPosition(location);

    /*auto moveTo = MoveTo::create(1, location);
    this->mySprite->stopAllActions();
    this->mySprite->runAction(moveTo);*/

    // 
    /*this->mouseLoc = location;
    this->direction = location - this->mySprite->getPosition();
    this->direction.normalize();*/


    if (this->isDragDrop) {
        this->mySprite->setPosition(location);
    }

    //8. Aim to mouse location
    Vec2 direction = location - this->mySprite->getPosition();
    float radian = direction.getAngle(Vec2(0, 1));
    float angle = radian * 180 / M_PI;
    this->mySprite->setRotation(angle);
}

void Lesson4Continue::shootingBullet(Vec2 targetPos) {
    // create bullet at sprite position and aim to targetPos
    auto bullet = Sprite::create("rocket.png");
    bullet->setContentSize(Size(30, 50));
    bullet->setPosition(this->mySprite->getPosition());
    addChild(bullet);
    Vec2 direction = targetPos - this->mySprite->getPosition();
    float radian = direction.getAngle(Vec2(0, 1));
    float angle = radian * 180 / M_PI;
    bullet->setRotation(angle);

    // shooting bullet to targetPos
    auto moveTo = MoveTo::create(1, targetPos);
    auto cleanUp = CallFunc::create([=]() {
        bullet->removeFromParentAndCleanup(true);
    });
    auto sequence = Sequence::create(moveTo, cleanUp, nullptr);
    bullet->runAction(sequence);
}