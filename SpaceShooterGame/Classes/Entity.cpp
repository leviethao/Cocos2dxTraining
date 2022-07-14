#include "Entity.h"
#include "Constant.h"

USING_NS_CC;

Entity::Entity() {

}

Entity::Entity(const string& file) {
    this->sprite = Sprite::create(file);

    this->body = PhysicsBody::createBox(this->sprite->getContentSize());
    this->body->setDynamic(false);
    this->sprite->addComponent(body);
    this->sprite->setTag((int)ContactType::None);

    this->init();
}

Entity::~Entity() {

}

void Entity::init()
{
    this->speed = 0;
    this->direction = Vec2::ZERO;
}

void Entity::update(float dt) {
}

void Entity::setSpeed(float speed) {
    this->speed = speed;
    this->body->setVelocity(direction * speed);
}

float Entity::getSpeed() {
    return this->speed;
}

void Entity::setDirection(Vec2 direction) {
    this->direction = direction;
    this->body->setVelocity(direction * speed);
}

Vec2 Entity::getDirection() {
    return this->direction;
}

Sprite* Entity::getSprite() {
    return this->sprite;
}

void Entity::destroy() {
    this->sprite->removeFromParentAndCleanup(true);
}
