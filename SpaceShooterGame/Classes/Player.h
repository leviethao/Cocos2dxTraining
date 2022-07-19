#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "cocos2d.h"
#include "Entity.h"
#include "Bullet.h"
#include "GunLV2.h"

USING_NS_CC;

class Player : public Entity
{
private:
	Bullet* bullet;
	std::vector<GunLV2*> guns;

	float exp;
	float level;
	int heart;

	void initEventListener();
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
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
	void levelUp();
};

#endif // __PLAYER_H__
