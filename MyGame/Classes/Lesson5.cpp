
#include "Lesson5.h"

USING_NS_CC;

Scene* Lesson5::createScene()
{
    return Lesson5::create();
}

// on "init" you need to initialize your instance
bool Lesson5::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::initWithPhysics() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    this->mySprite = Sprite::create("player.png");
    addChild(this->mySprite);
    this->mySprite->setPosition(Vec2(50, 50));


    this->mySprite2 = Sprite::create("player.png");
    addChild(this->mySprite2);
    this->mySprite2->setPosition(Vec2(300, 200));

    // Init mouse event listener
    auto mouseListener = EventListenerMouse::create();
    mouseListener->onMouseDown = CC_CALLBACK_1(Lesson5::onMouseDown, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);


    this->initContactListener();
    this->scheduleUpdate();
    return true;
}


void Lesson5::update(float dt) {
    // Handle update game state here
  
    // Detect collision basic
    /*Vec2 r = Vec2(this->mySprite->getContentSize().width / 2 + this->mySprite2->getContentSize().width / 2,
        this->mySprite->getContentSize().height / 2 + this->mySprite2->getContentSize().height / 2);

    float distance = (this->mySprite2->getPosition() - this->mySprite->getPosition()).length();

    if (distance <= r.x || distance <= r.y) {
        this->mySprite->setColor(Color3B::RED);
        this->mySprite2->setColor(Color3B(255, 0, 0));
    }
    else {
        this->mySprite->setColor(Color3B::WHITE);
        this->mySprite2->setColor(Color3B(255, 255, 255));
    }*/
}

void Lesson5::onMouseDown(Event* event) {
    EventMouse* e = (EventMouse*)event;

    Vec2 location = e->getLocationInView();

    auto moveTo = MoveTo::create(1, location);
    this->mySprite->stopAllActions();
    this->mySprite->runAction(moveTo);
}

void Lesson5::initContactListener() {
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = [](PhysicsContact& contact) {
        Node* nodeA = contact.getShapeA()->getBody()->getNode();
        Node* nodeB = contact.getShapeB()->getBody()->getNode();

        if (nodeA && nodeB) {
            if (nodeA->getTag() == 10) {
                nodeB->setColor(Color3B::RED);
            }
            else if (nodeB->getTag() == 10) {
                nodeA->setColor(Color3B::RED);
            }
        }
        return true;
    };
    contactListener->onContactSeparate = CC_CALLBACK_1(Lesson5::onContactSeparate, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

    // init physic body
    auto physicsBody = PhysicsBody::createCircle(this->mySprite->getContentSize().width / 2);
    physicsBody->setDynamic(false);
    physicsBody->setContactTestBitmask(0x01); //0001
    physicsBody->setCategoryBitmask(0x01); // 0001
    physicsBody->setCollisionBitmask(0x01); // 0001
    this->mySprite->addComponent(physicsBody);
    this->mySprite->setTag(10); // identity for mySprite

    auto physicsBody2 = PhysicsBody::createCircle(this->mySprite2->getContentSize().width / 2);
    physicsBody2->setDynamic(false);
    physicsBody2->setContactTestBitmask(0x01); // 0010 
    physicsBody2->setCategoryBitmask(0x03); // 0011
    physicsBody2->setCollisionBitmask(0x01); // 0001
    this->mySprite2->addComponent(physicsBody2);
    this->mySprite2->setTag(1); //identity for mySprite2

    //((catetegory1 & collision2) > 0)  &&
    // ((cateroty2 & collision1) > 0)
    // => collision = true

    // Cach tinh & tren bit
    // 0001
    // 0101
    //  001
}

// When collision ended
void Lesson5::onContactSeparate(PhysicsContact& contact) {
    Node* nodeA = contact.getShapeA()->getBody()->getNode();
    Node* nodeB = contact.getShapeB()->getBody()->getNode();

    if (nodeA && nodeB) {
        nodeA->setColor(Color3B::WHITE);
        nodeB->setColor(Color3B(255, 255, 255));
    }
}