#include "Bullet.h"

USING_NS_CC;

Bullet::Bullet(ContactType contactType):Entity(contactType == ContactType::PlayerBullet ? "PlayerBullet.png" : "EnemyBullet.png") {
	this->sprite->setTag((int)contactType);
	switch (contactType) {
	case ContactType::EnemyBullet:
		this->body->setContactTestBitmask(ENEMY_BULLET_CONTACT_TEST_BITMASK);
		this->body->setCategoryBitmask(ENEMY_BULLET_CATEGORY_BITMASK);
		this->body->setCollisionBitmask(ENEMY_BULLET_COLLISION_BITMASK);
		break;
	case ContactType::PlayerBullet:
		this->body->setContactTestBitmask(PLAYER_BULLET_CONTACT_TEST_BITMASK);
		this->body->setCategoryBitmask(PLAYER_BULLET_CATEGORY_BITMASK);
		this->body->setCollisionBitmask(PLAYER_BULLET_COLLISION_BITMASK);
		break;
	}
	inUse = false;
	this->init();
}

Bullet::~Bullet() {

}

void Bullet::init()
{
	Entity::init();

	this->damage = this->sprite->getTag() == (int)ContactType::PlayerBullet ? 20 : 10;
	this->maxHP = 1;
	this->hp = 1;
}

void Bullet::setInUse(bool inUse) {
	this->inUse = inUse;

	if (!this->inUse) {
		this->sprite->removeFromParentAndCleanup(true);
		this->init();
	}
}

bool Bullet::getInUse() {
	return this->inUse;
}
