#ifndef __BULLET_H__
#define __BULLET_H__

#include "cocos2d.h"
#include "Entity.h"
#include "Constant.h"

USING_NS_CC;

class Bullet : public Entity
{
private:
	bool inUse;
public:
	enum Type {
		PlayerBullet,
		RaptorBullet
	};

	Bullet(ContactType contactType);
	~Bullet();
	void init();
	void setInUse(bool inUse);
	bool getInUse();
};

#endif // __BULLET_H__
