
#include "Lesson3.h"

USING_NS_CC;

Scene* Lesson3::createScene()
{
    return Lesson3::create();
}

// on "init" you need to initialize your instance
bool Lesson3::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    this->scheduleUpdate();


    this->mySprite = Sprite::create("player.png");
    addChild(this->mySprite);
    this->mySprite->setPosition(Vec2(50, 50));

    // Sequence
    /*auto moveTo = MoveTo::create(2, Vec2(200, 100));
    auto rotateBy = RotateBy::create(2, 360);
    auto scaleTo = ScaleTo::create(2, 5);
    auto sequence = Sequence::create(moveTo, rotateBy, scaleTo, nullptr);
    mySprite->runAction(sequence);*/


    // Easing
    /*auto moveTo = MoveTo::create(2, Vec2(200, 100));
    auto easeBounceIn = EaseBounceIn::create(moveTo->clone());
    this->mySprite->runAction(easeBounceIn);*/

    // Bouncing action
    auto moveBy = MoveBy::create(2, Vec2(100, 100));
    auto move_ease_in = EaseBounceIn::create(moveBy->clone());
    auto move_ease_in_back = move_ease_in->reverse();

    auto delay = DelayTime::create(0.25);

    auto sequence = Sequence::create(move_ease_in, delay, move_ease_in_back, delay->clone(), nullptr);

    this->mySprite->runAction(RepeatForever::create(sequence));


    return true;
}


void Lesson3::update(float dt) {
    // Handle update game state here


    // Move mySprite by direction
    //Vec2 direction = Vec2(10, 10);
    //direction.normalize(); // unit vector \
    //const float speed = 100;
    //auto curPosition = this->mySprite->getPosition();
    //Vec2 newPosition = Vec2(curPosition.x + (speed * dt * direction.x),
    //    curPosition.y + (speed * dt * direction.y));
    //this->mySprite->setPosition(newPosition);

    // Rotate mySprite
    /*float rotateSpeed = 180;
    float rotateDirection = -1;
    auto curAngle = this->mySprite->getRotation();
    float newAngle = curAngle + rotateSpeed * dt * rotateDirection;
    this->mySprite->setRotation(newAngle);*/
}

