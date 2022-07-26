
#include "ui/CocosGUI.h"
#include "Lesson16.h"


USING_NS_CC;


Scene* Lesson16::createScene()
{
    return Lesson16::create();
}

// on "init" you need to initialize your instance
bool Lesson16::init()
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
	mouseListener->onMouseDown = CC_CALLBACK_1(Lesson16::onMouseDown, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

	// Init keyboard listener
	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(Lesson16::onKeyPressed, this);
	keyboardListener->onKeyReleased = CC_CALLBACK_2(Lesson16::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);


	//
	this->mySprite = Sprite::create("player.png");
	this->mySprite->setPosition(200, 200);
	addChild(mySprite);

	this->direction = Vec2::ZERO;
	this->speed = 200;

    this->scheduleUpdate();
    
	return true;
}


void Lesson16::update(float dt) {
    // Handle update game state here

	this->mySprite->setPosition(mySprite->getPosition() + this->speed * dt * this->direction);
}


void Lesson16::onMouseDown(Event* event) {
    EventMouse* e = (EventMouse*)event;
    Vec2 location = e->getLocationInView();

    Vec2 direction = location - this->mySprite->getPosition();
    direction.normalize();
}



void Lesson16::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {
	auto newDirection = direction;

	switch (keyCode) {
	case EventKeyboard::KeyCode::KEY_W:
		newDirection.y = 1;
		break;
	case EventKeyboard::KeyCode::KEY_S:
		newDirection.y = -1;
		break;
	case EventKeyboard::KeyCode::KEY_A:
		newDirection.x = -1;
		break;
	case EventKeyboard::KeyCode::KEY_D:
		newDirection.x = 1;
		break;
	default:
		break;
	}

	newDirection.normalize();
	this->direction = newDirection;
}

void Lesson16::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {
	auto newDirection = direction;

	switch (keyCode) {
	case EventKeyboard::KeyCode::KEY_W:
	case EventKeyboard::KeyCode::KEY_S:
		newDirection.y = 0;
		break;
	case EventKeyboard::KeyCode::KEY_A:
	case EventKeyboard::KeyCode::KEY_D:
		newDirection.x = 0;
		break;
	default:
		break;
	}

	newDirection.normalize();
	this->direction = newDirection;
}