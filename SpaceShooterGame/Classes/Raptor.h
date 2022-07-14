#ifndef __RAPTOR_H__
#define __RAPTOR_H__

#include "cocos2d.h"
#include "Entity.h"
#include "Bullet.h"
#include "BulletPool.h"

USING_NS_CC;

class Raptor : public Entity
{
private:
	BulletPool* bulletPool;
public:
	void shootingScheduler(float dt);
	Raptor();
	~Raptor();
	void init();
	void update(float dt);
	void shooting(Vec2 aimDirection);
};

#endif // __RAPTOR_H__
