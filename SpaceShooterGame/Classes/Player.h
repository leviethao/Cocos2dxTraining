#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "cocos2d.h"
#include "Entity.h"
#include "Bullet.h"

USING_NS_CC;

class Player : public Entity
{
private:
	Bullet* bullet;

	float exp;
	float level;
	int heart;
public:
	Player();
	~Player();
	void init();
	void update(float dt);
	void shooting();
	void setIsShooting(bool isShooting);
	void takeDamage(float damage);
	int getHeart();
	void setHeart(int heart);
	void die();
};

#endif // __PLAYER_H__
