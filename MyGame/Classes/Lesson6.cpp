
#include "Lesson6.h"

USING_NS_CC;

Scene* Lesson6::createScene()
{
    return Lesson6::create();
}

// on "init" you need to initialize your instance
bool Lesson6::init()
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
    mouseListener->onMouseDown = CC_CALLBACK_1(Lesson6::onMouseDown, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

    this->initPhysics();

    this->scheduleUpdate();
    return true;
}


void Lesson6::update(float dt) {
    // Handle update game state here
 
}

void Lesson6::onMouseDown(Event* event) {
    EventMouse* e = (EventMouse*)event;

    Vec2 location = e->getLocationInView();

    this->mySprite->setPosition(location);
}

void Lesson6::initPhysics() {
    // init physic body
    auto physicsBody = PhysicsBody::createCircle(this->mySprite->getContentSize().width / 2, PhysicsMaterial(1, 1, 0.5));
    //physicsBody->setDynamic(false);
    physicsBody->setContactTestBitmask(0x01); //0001
    this->mySprite->addComponent(physicsBody);
    physicsBody->setMass(100000);


    auto physicsBody2 = PhysicsBody::createBox(this->mySprite2->getContentSize(), PhysicsMaterial(100, 1, 0));
    
    // Set static physics body
    //physicsBody2->setDynamic(false);

    // Velocity
    //physicsBody2->setVelocity(Vec2(300, 200));
    //physicsBody2->setLinearDamping(0.5);
    //physicsBody2->setVelocityLimit(30);

    //physicsBody2->setAngularVelocity(20);
    //physicsBody2->setAngularDamping(0.2);
    //physicsBody2->setAngularVelocityLimit(5);

    
    //physicsBody2->setDynamic(false);
    physicsBody2->setContactTestBitmask(0x01); // 0010 
    this->mySprite2->addComponent(physicsBody2);

    //physicsBody2->setGravityEnable(false);
    //physicsBody2->setMass(10000);
    

    // Create sprite with physics body polygon
    /*this->mySprite3 = Sprite::create("player.png");
    addChild(this->mySprite3);
    this->mySprite3->setPosition(Vec2(300, 300));
    Vec2 points[5] = { Vec2(-30, 30), Vec2(-30, -30), Vec2(0.5, 60), Vec2(30, 40), Vec2(30, -50) };
    auto physicsBody3 = PhysicsBody::createPolygon(points, 5);
    this->mySprite3->addComponent(physicsBody3);*/

    this->getPhysicsWorld()->setGravity(Vec2(0, 0));

    //add bounding box
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto edgeBox = PhysicsBody::createEdgeBox(visibleSize,
        PhysicsMaterial(1, 1, 0), 5);
    Node* edgeNode = Node::create();
    edgeNode->addComponent(edgeBox);
    edgeNode->setPosition(Vec2(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height / 2));
    addChild(edgeNode);
}