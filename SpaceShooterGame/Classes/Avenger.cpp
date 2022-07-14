#include "Avenger.h"
#include "GameManager.h"
#include "Player.h"

USING_NS_CC;

Avenger::Avenger(): Entity("Avenger.png") {
	this->body->setContactTestBitmask(ENEMY_CONTACT_TEST_BITMASK);
	this->body->setCategoryBitmask(ENEMY_CATEGORY_BITMASK);
	this->body->setCollisionBitmask(ENEMY_COLLISION_BITMASK);
	
	this->sprite->setTag((int)ContactType::Enemy);
}

Avenger::~Avenger() {

}

void Avenger::init()
{
	this->setSpeed(50);
	this->setDirection(Vec2(1, 1));
}

void Avenger::update(float dt) {
	Player* player = GameManager::getPlayer();
	auto direct = player->getSprite()->getPosition() - this->sprite->getPosition();
	direct.normalize();
	this->setDirection(direct);
}
