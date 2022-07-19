#include "Player.h"
#include "Bullet.h"
#include "GameManager.h"

USING_NS_CC;

Player::Player(): Entity("Player.png") {
	this->body->setContactTestBitmask(PLAYER_CONTACT_TEST_BITMASK);
	this->body->setCategoryBitmask(PLAYER_CATEGORY_BITMASK);
	this->body->setCollisionBitmask(PLAYER_COLLISION_BITMASK);

	this->init();
}

Player::~Player() {

}

void Player::init()
{
	this->setMaxHP(100);
	this->setHP(100);
	this->damage = 100;
	this->heart = 1;
	this->level = 1;
	this->setSpeed(300);

	this->initEventListener();
}

void Player::shooting() {
	auto aimAngle = this->sprite->getRotation() * -1;
	Vec2 aimDirection = Vec2(0, 1);
	aimDirection.rotate(Vec2(0, 0), aimAngle * M_PI / 180);
	aimDirection.normalize();
	
	this->bullet = new Bullet(ContactType::PlayerBullet);
	this->bullet->init();
	Sprite* sBullet = bullet->getSprite();
	//sBullet->setContentSize(Size(20, 30));
	sBullet->setPosition(this->sprite->getPosition() + aimDirection * 10);
	float radian = aimDirection.getAngle(Vec2(0, 1));
	float angle = radian * 180 / M_PI;
	sBullet->setRotation(angle);
	bullet->setSpeed(400);
	bullet->setDirection(aimDirection);
	GameManager::addEntity(bullet);

	// Shooting guns
	for (GunLV2* gun : this->guns) {
		gun->shooting();
	}
}

void Player::setIsShooting(bool isShooting) {
	if (isShooting) {
		this->sprite->schedule([&](float dt) {
			this->shooting();
		}, 0.1, "PlayerShooting");
	}
	else {
		this->sprite->unschedule("PlayerShooting");
	}
}

void Player::takeDamage(float damage) {
	this->hp -= damage;
	if (this->hp <= 0) {
		if (this->heart > 0) {
			this->heart--;
			this->hp = this->maxHP;
		}
		else {
			this->hp = 0;
		}
	}
}

int Player::getHeart() {
	return this->heart;
}

void Player::setHeart(int heart) {
	this->heart = heart;
}

void Player::die() {
	auto node = Node::create();
	node->scheduleOnce([&](float dt) {
		GameManager::end();
	}, 5, "EndGame");
	GameManager::getWorld()->addChild(node);
	
	this->pause();
}

void Player::update(float dt) {
	if (this->hp <= 0) {
		this->die();
	}
}

void Player::initEventListener() {
	// Init mouse event listener
	auto mouseListener = EventListenerMouse::create();
	mouseListener->onMouseDown = [&](Event* event) {
		EventMouse* e = (EventMouse*)event;
		Vec2 location = e->getLocationInView();
		this->setIsShooting(true);
	};
	mouseListener->onMouseUp = [&](Event* event) {
		EventMouse* e = (EventMouse*)event;
		Vec2 location = e->getLocationInView();

		this->setIsShooting(false);
	};
	mouseListener->onMouseMove = [&](Event* event) {
		EventMouse* e = (EventMouse*)event;
		Vec2 location = e->getLocationInView();
		location = GameManager::getWorld()->getDefaultCamera()->convertToWorldSpaceAR(location - GameManager::getVisibleSize() / 2);
		
		//Aim to mouse location
		Vec2 aimDirection = location - this->getSprite()->getPosition();
		float radian = aimDirection.getAngle(Vec2(0, 1));
		float angle = radian * 180 / M_PI;
		this->getSprite()->setRotation(angle);
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseListener, this->sprite);


	// Init keyboard event listeners
	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(Player::onKeyPressed, this);
	keyboardListener->onKeyReleased = CC_CALLBACK_2(Player::onKeyReleased, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this->sprite);
}



void Player::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {
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
	setDirection(newDirection);
}

void Player::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {
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
	setDirection(newDirection);
}

void Player::levelUp() {
	this->level++;
	if (this->level == 2) {
		GunLV2* gunLV2 = new GunLV2();
		gunLV2->getSprite()->setPosition(Vec2(sprite->getContentSize().width / 2, 0));
		this->sprite->addChild(gunLV2->getSprite());
		this->guns.push_back(gunLV2);
	}
}

