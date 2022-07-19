#include "GunLV2.h"
#include "Bullet.h"
#include "GameManager.h"

USING_NS_CC;

GunLV2::GunLV2(): Entity("GunLV2.png") {

	this->leftGun = Sprite::create("GunLV2.png");
	this->rightGun = Sprite::create("GunLV2.png");
	this->sprite = Sprite::create();
	
	leftGun->setPosition(Vec2(-20, 0) + sprite->getContentSize() / 2);
	rightGun->setPosition(Vec2(20, 0) + sprite->getContentSize() / 2);
	
	this->sprite->addChild(leftGun);
	this->sprite->addChild(rightGun);
	log("gun size: %.2f, %.2f", this->getSprite()->getContentSize().width, this->getSprite()->getContentSize().height);

	// Not collision
	this->body->setContactTestBitmask(0x00);
	this->body->setCategoryBitmask(0x00);
	this->body->setCollisionBitmask(0x00);

	this->init();
}

GunLV2::~GunLV2() {

}

void GunLV2::init()
{
}

void GunLV2::shooting() {
	auto aimAngle = this->sprite->getRotation() * -1;
	Vec2 aimDirection = Vec2(0, 1);
	aimDirection.rotate(Vec2(0, 0), aimAngle * M_PI / 180);

	auto point1 = aimDirection;
	auto point2 = aimDirection * 10;
	auto point1WorldSpace = GameManager::getWorld()->convertToNodeSpace(sprite->getParent()->convertToWorldSpace(point1));
	auto point2WorldSpace = GameManager::getWorld()->convertToNodeSpace(sprite->getParent()->convertToWorldSpace(point2));
	aimDirection = point2WorldSpace - point1WorldSpace;

	aimDirection.normalize();
	
	// Left bullet
	auto bullet = new Bullet(ContactType::PlayerBullet);
	bullet->init();
	Sprite* sBullet = bullet->getSprite();
	//sBullet->setContentSize(Size(20, 30));
	auto bulletPosWorldSpace = GameManager::getWorld()->convertToNodeSpace(sprite->convertToWorldSpace(leftGun->getPosition()));
	sBullet->setPosition(bulletPosWorldSpace + aimDirection * 10);
	float radian = aimDirection.getAngle(Vec2(0, 1));
	float angle = radian * 180 / M_PI;
	sBullet->setRotation(angle);
	bullet->setSpeed(400);
	bullet->setDirection(aimDirection);
	GameManager::addEntity(bullet);

	// Right bullet
	bullet = new Bullet(ContactType::PlayerBullet);
	bullet->init();
	sBullet = bullet->getSprite();
	//sBullet->setContentSize(Size(20, 30));
	bulletPosWorldSpace = GameManager::getWorld()->convertToNodeSpace(sprite->convertToWorldSpace(rightGun->getPosition()));
	sBullet->setPosition(bulletPosWorldSpace + aimDirection * 10);
	radian = aimDirection.getAngle(Vec2(0, 1));
	angle = radian * 180 / M_PI;
	sBullet->setRotation(angle);
	bullet->setSpeed(400);
	bullet->setDirection(aimDirection);
	GameManager::addEntity(bullet);
}

void GunLV2::update(float dt) {
}
