#include "Raptor.h"
#include "Bullet.h"
#include "GameManager.h"

USING_NS_CC;

Raptor::Raptor(): Entity("Raptor.png") {
	this->body->setContactTestBitmask(ENEMY_CONTACT_TEST_BITMASK);
	this->body->setCategoryBitmask(ENEMY_CATEGORY_BITMASK);
	this->body->setCollisionBitmask(ENEMY_COLLISION_BITMASK);

	this->sprite->setTag((int)ContactType::Enemy);

	this->bulletPool = new BulletPool(ContactType::EnemyBullet);
	//bulletPool->create()->get
}

Raptor::~Raptor() {

}

void Raptor::init()
{
	this->setSpeed(50);
	this->damage = 20;
	this->maxHP = 50;
	this->hp = 50;
	//this->shooting(Vec2(1, 1));
	// Schedule shooting
	
	/*cocos2d::ccSchedulerFunc scheF = [&](float dt) {
		this->shooting(this->getDirection());
	};*/
	//Director::getInstance()->getScheduler()->schedule(CC_CALLBACK_1(Raptor::shootingScheduler, this), this, 1.0f, false);
	/*this->sprite->schedule(CC_CALLBACK_1(Raptor::shootingScheduler, this), 1.0f);*/
	this->sprite->schedule([&](float dt) mutable {
		this->shooting(this->getDirection());
		}, 1, "RaptorShooting");
}

void Raptor::shootingScheduler(float dt) {

}

void Raptor::shooting(Vec2 aimDirection) {
	aimDirection.normalize();
	auto bullet = new Bullet(ContactType::EnemyBullet); //bulletPool->create();
	bullet->init();
	Sprite* sBullet = bullet->getSprite();
	//sBullet->setContentSize(Size(20, 30));
	sBullet->setPosition(this->sprite->getPosition() + aimDirection * 10);
	float radian = aimDirection.getAngle(Vec2(0, 1));
	float angle = radian * 180 / M_PI;
	sBullet->setRotation(angle);
	bullet->setSpeed(100);
	bullet->setDirection(aimDirection);
	GameManager::addEntity(bullet);
}

void Raptor::update(float dt) {
	auto aimDirection = GameManager::getPlayer()->getSprite()->getPosition() - this->sprite->getPosition();
	aimDirection.normalize();
	this->setDirection(aimDirection);
	float radian = aimDirection.getAngle(Vec2(0, 1));
	float angle = radian * 180 / M_PI;
	this->sprite->setRotation(angle);
}
