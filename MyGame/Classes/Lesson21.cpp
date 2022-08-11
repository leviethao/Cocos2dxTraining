
#include "Lesson21.h"

USING_NS_CC;

Scene* Lesson21::createScene()
{
    return Lesson21::create();
}

// on "init" you need to initialize your instance
bool Lesson21::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::initWithPhysics() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// Init keyboard listener
	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(Lesson21::onKeyPressed, this);
	keyboardListener->onKeyReleased = CC_CALLBACK_2(Lesson21::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

	auto back1 = Sprite::create("back.jpg");
	back1->setAnchorPoint(Vec2(0, 0));
	back1->setContentSize(Size(visibleSize.width * 1.5, visibleSize.height));

    auto back2 = Sprite::create("back.jpg");
	back2->setAnchorPoint(Vec2(0, 0));
    back2->setContentSize(Size(visibleSize.width * 1.5, visibleSize.height));
	back2->setPosition(Vec2(back1->getPositionX() + back1->getContentSize().width + 10,
		back1->getPositionY()));
    
	auto back = Node::create();
	back->setContentSize(visibleSize);
	back->setAnchorPoint(Vec2(0, 0));
	back->addChild(back1);
	back->addChild(back2);

	this->backList.push_back(back1);
	this->backList.push_back(back2);

    auto front1 = Sprite::create("front.jpg");
	front1->setContentSize(Size(visibleSize.width * 1.5, visibleSize.height * 0.3));
	front1->setAnchorPoint(Vec2(0, 0));
	auto front2 = Sprite::create("front.jpg");
	front2->setContentSize(Size(visibleSize.width * 1.5, visibleSize.height * 0.3));
	front2->setAnchorPoint(Vec2(0, 0));
	auto front = Node::create();
	front->setContentSize(Size(visibleSize.width, visibleSize.height * 0.3));
	front->setAnchorPoint(Vec2(0, 0));
	front->addChild(front1);
	front->addChild(front2);
	//
	front2->setPosition(Vec2(front1->getPositionX() + front1->getContentSize().width + 10,
		front1->getPositionY()));
	
	this->frontList.push_back(front1);
	this->frontList.push_back(front2);

    this->parallaxNode = ParallaxNode::create();
    this->parallaxNode->addChild(back, -1, Vec2(0.2, 1), Vec2::ZERO);
    this->parallaxNode->addChild(front, 1, Vec2(1, 1), Vec2(0, 0));

    this->parallaxNode->setPosition(origin);
    addChild(this->parallaxNode);
	this->startPos = this->parallaxNode->getPosition();

	this->backgroundSpeed = 1000;
	this->backgroundDirection = Vec2::ZERO;

	this->player = new Player();
	addChild(this->player->sprite);
	this->player->sprite->setPosition(visibleSize / 2);

	// create land body
	getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	getPhysicsWorld()->setGravity(Vec2(0, -980));
	auto landBody = PhysicsBody::createBox(front1->getContentSize());
	landBody->setDynamic(false);
	auto landBody2 = PhysicsBody::createBox(front2->getContentSize());
	landBody2->setDynamic(false);
	front1->addComponent(landBody);
	front2->addComponent(landBody2);

	// create obstacles
	const int OBSTACLES_NUM = 5;
	for (int i = 0; i < 5; i++) {
		auto obstacle = Sprite::create();
		obstacle->setContentSize(Size(50, 100));
		obstacle->setColor(Color3B::RED);
		obstacle->setPosition(600, 400);
		auto body = PhysicsBody::createBox(obstacle->getContentSize(),
			PhysicsMaterial(0.9, 0, 0));
		body->setMass(30000);
		obstacle->addComponent(body);
		front->addChild(obstacle);
	}

	scheduleUpdate();
    return true;
}




void Lesson21::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {

	switch (keyCode) {
	case EventKeyboard::KeyCode::KEY_W:
		this->player->jump();
		break;
	case EventKeyboard::KeyCode::KEY_S:
		break;
	case EventKeyboard::KeyCode::KEY_A:
		backgroundDirection.x = 1;
		this->player->sprite->setFlippedX(true);
		break;
	case EventKeyboard::KeyCode::KEY_D:
		this->player->sprite->setFlippedX(false);
		backgroundDirection.x = -1;
		break;
	default:
		break;
	}

	backgroundDirection.normalize();
}

void Lesson21::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {

	switch (keyCode) {
	case EventKeyboard::KeyCode::KEY_W:
	case EventKeyboard::KeyCode::KEY_S:
		break;
	case EventKeyboard::KeyCode::KEY_A:
	case EventKeyboard::KeyCode::KEY_D:
		backgroundDirection.x = 0;
		break;
	default:
		break;
	}

	backgroundDirection.normalize();
}



void Lesson21::update(float dt) {
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	float delta = (parallaxNode->getPositionX() - startPos.x) * -1;
	scrollParallax(delta, frontList);
	scrollParallax(delta * 0.2, backList);

	// move background
	Vec2 currentPosition = parallaxNode->getPosition();
	this->parallaxNode->setPosition(currentPosition.x + 
		backgroundSpeed * dt * backgroundDirection.x, currentPosition.y);
}

void Lesson21::scrollParallax(float delta, std::vector<Sprite*> &list) {
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	float leftEdge = list[0]->getPositionX() + 50;
	float rightEdge = list[1]->getPositionX() + list[1]->getContentSize().width - 50;

	if (delta + visibleSize.width > rightEdge) {
		float list0X = list[1]->getPositionX() + list[1]->getContentSize().width + 10;

		list[0]->setPosition(list0X, list[0]->getPositionY());

		Sprite* temp = list[0];
		list[0] = list[1];
		list[1] = temp;
		log("to right edge");
	}
	else if (delta <leftEdge) {
		float list1X = list[0]->getPositionX() - list[1]->getContentSize().width - 10;

		list[1]->setPosition(list1X, list[1]->getPositionY());

		Sprite* temp = list[0];
		list[0] = list[1];
		list[1] = temp;
		log("to left edge");
	}
}

Player::Player() {
	this->sprite = Sprite::create("Player.png");
	this->sprite->setContentSize(Size(100, 100));
	this->body = PhysicsBody::createBox(Size(50, 90), PhysicsMaterial(0.9f, 0, 0));
	this->body->setMass(10000);
	this->direction = Vec2::ZERO;
	this->sprite->addComponent(this->body);
	this->jumpFac = 400;
}

Player::~Player() {

}

void Player::move() {

}

void Player::jump() {
	this->body->setVelocity(Vec2(0, this->jumpFac));
}