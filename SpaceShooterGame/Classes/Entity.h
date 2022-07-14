#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "cocos2d.h"

USING_NS_CC;
using namespace std;

class Entity
{
private:
protected:
    Sprite* sprite;
    float speed;
    Vec2 direction;
    PhysicsBody* body;

public:
    enum Enemies {
        Avenger,
        Raptor
    };

    Entity();
    Entity(const string& file);
    ~Entity();
    virtual void init();
    virtual void update(float dt);
    virtual void destroy();
    void setSpeed(float speed);
    float getSpeed();
    void setDirection(Vec2 direction);
    Vec2 getDirection();
    Sprite* getSprite();
};

#endif // __ENTITY_H__
