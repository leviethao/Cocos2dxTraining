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
	this->setSpeed(100);
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
	bullet->setSpeed(200);
	bullet->setDirection(aimDirection);
	GameManager::addEntity(bullet);
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
	this->body->setVelocity(Vec2::ZERO);
	this->sprite->pause();
	auto node = Node::create();
	node->scheduleOnce([&](float dt) {
		GameManager::end();
	}, 5, "EndGame");
	GameManager::getWorld()->addChild(node);
	GameManager::getWorld()->pause();

}

void Player::update(float dt) {
	if (this->hp <= 0) {
		this->die();
	}
}