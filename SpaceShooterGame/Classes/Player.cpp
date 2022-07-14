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
	GameManager::getWorld()->addChild(sBullet);
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
