#ifndef __GUN_LV2_H__
#define __GUN_LV2_H__

#include "cocos2d.h"
#include "Entity.h"
#include "Bullet.h"

USING_NS_CC;

class GunLV2 : public Entity
{
private:
	Sprite* leftGun;
	Sprite* rightGun;
public:
	GunLV2();
	~GunLV2();
	void init();
	void update(float dt);
	void shooting();
};

#endif // __GUN_LV2_H__
