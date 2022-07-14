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
public:
	Player();
	~Player();
	void init();
	void shooting();
	void setIsShooting(bool isShooting);
};

#endif // __PLAYER_H__
