#include "Entity.h"
#include "Constant.h"
#include "GameManager.h"

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
    this->maxHP = 0;
    this->hp = 0;
    this->damage = 0;
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

float Entity::getHP() {
    return this->hp;
}

void Entity::setHP(float hp) {
    this->hp = hp;
}

float Entity::getDamage() {
    return this->damage;
}

void Entity::setDamage(float damage) {
    this->damage = damage;
}

void Entity::takeDamage(float damage) {
    this->hp -= damage;
    log("%d HP = %.2f", this->sprite->getTag(), this->hp);
    if (this->hp <= 0) { 
        this->hp = 0;
        this->sprite->setVisible(false);
        GameManager::destroyEntity(this);
    }
}

void Entity::setMaxHP(float maxHP) {
    this->maxHP = maxHP;
}

float Entity::getMaxHP() {
    return this->maxHP;
}
