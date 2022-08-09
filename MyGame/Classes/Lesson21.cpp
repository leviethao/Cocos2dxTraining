
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
    if ( !Scene::init() )
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

    auto back = Sprite::create("back.png");
	back->setAnchorPoint(Vec2(0, 0));
    back->setContentSize(Size(visibleSize.width * 1.5, visibleSize.height));
    
    auto front1 = Sprite::create("front.png");
	front1->setContentSize(Size(visibleSize.width * 1.5, visibleSize.height * 0.5));
	front1->setAnchorPoint(Vec2(0, 0));
	auto front2 = Sprite::create("front.png");
	front2->setContentSize(Size(visibleSize.width * 1.5, visibleSize.height * 0.5));
	front2->setAnchorPoint(Vec2(0, 0));
	auto front = Node::create();
	front->setContentSize(visibleSize);
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

	scheduleUpdate();
    return true;
}




void Lesson21::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {

	switch (keyCode) {
	case EventKeyboard::KeyCode::KEY_W:
		break;
	case EventKeyboard::KeyCode::KEY_S:
		break;
	case EventKeyboard::KeyCode::KEY_A:
		this->parallaxNode->stopAllActions();
		this->parallaxNode->runAction(MoveBy::create(2, Vec2(2000, 0)));
		break;
	case EventKeyboard::KeyCode::KEY_D:
		this->parallaxNode->stopAllActions();
		this->parallaxNode->runAction(MoveBy::create(2, Vec2(-2000, 0)));
		break;
	default:
		break;
	}

}

void Lesson21::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {

	switch (keyCode) {
	case EventKeyboard::KeyCode::KEY_W:
	case EventKeyboard::KeyCode::KEY_S:
		break;
	case EventKeyboard::KeyCode::KEY_A:
	case EventKeyboard::KeyCode::KEY_D:
		this->parallaxNode->stopAllActions();
		break;
	default:
		break;
	}

}

void Lesson21::update(float dt) {
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	float delta = (parallaxNode->getPositionX() - startPos.x) * -1;
	float frontLeftEdge = frontList[0]->getPositionX() + 50;
	float frontRightEdge = frontList[1]->getPositionX() + frontList[1]->getContentSize().width - 50;

	if (delta + visibleSize.width > frontRightEdge) {
		float front0X = frontList[1]->getPositionX() + frontList[1]->getContentSize().width + 10;
		
		frontList[0]->setPosition(front0X, frontList[0]->getPositionY());

		Sprite* temp = frontList[0];
		frontList[0] = frontList[1];
		frontList[1] = temp;
		log("to right edge");
	}
	else if (delta < frontLeftEdge) {
		float front1X = frontList[0]->getPositionX() - frontList[1]->getContentSize().width - 10;

		frontList[1]->setPosition(front1X, frontList[1]->getPositionY());

		Sprite* temp = frontList[0];
		frontList[0] = frontList[1];
		frontList[1] = temp;
		log("to left edge");
	}
	log("delta: %.2f, left: %.2f, right: %.2f",
		delta, frontLeftEdge, frontRightEdge);
}