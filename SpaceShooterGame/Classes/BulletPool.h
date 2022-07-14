#ifndef __BULLET_POOL_H__
#define __BULLET_POOL_H__

#include "cocos2d.h"
#include "Bullet.h"

USING_NS_CC;
using namespace std;

class BulletPool
{
private:
    std::vector<Bullet*> bullets;
    ContactType contactType;
public:
    BulletPool(ContactType contactType);
    ~BulletPool();

    Bullet* create();
};

#endif // __BULLET_POOL_H__
