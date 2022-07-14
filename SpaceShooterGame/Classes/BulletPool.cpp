#include "BulletPool.h"

USING_NS_CC;

const int BULLET_POOL_SIZE = 10;

BulletPool::BulletPool(ContactType contactType) {
	this->contactType = contactType;
	for (int i = 0; i < BULLET_POOL_SIZE; i++) {
		bullets.push_back(new Bullet(contactType));
	}
}

BulletPool::~BulletPool() {

}

Bullet* BulletPool::create() {
	for (Bullet* bullet : bullets) {
		if (bullet->getInUse() == false) {
			bullet->setInUse(true);
			return bullet;
		}
	}

	auto newBullet = new Bullet(this->contactType);
	bullets.push_back(newBullet);
	newBullet->setInUse(true);
	return newBullet;
}

