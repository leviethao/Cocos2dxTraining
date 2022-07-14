#ifndef __AVENGER_H__
#define __AVENGER_H__

#include "cocos2d.h"
#include "Entity.h"

USING_NS_CC;

class Avenger : public Entity
{
private:
public:
	Avenger();
	~Avenger();
	void init();
	void update(float dt);
};

#endif // __AVENGER_H__
