#ifndef __CONSTANT_H__
#define __CONSTANT_H__

#include "cocos2d.h"

USING_NS_CC;

enum class ContactType {
	None,
	Enemy,
	EnemyBullet,
	Player,
	PlayerBullet,
};

// Player can collide with: Enemy, Enemy Bullet
const int PLAYER_CONTACT_TEST_BITMASK = 0x06; // 0110
const int PLAYER_CATEGORY_BITMASK = 0x09; // 1001
const int PLAYER_COLLISION_BITMASK = 0xFFFFFFFF;

// Enemy can collide with: Player
const int ENEMY_CONTACT_TEST_BITMASK = 0x09; // 1001
const int ENEMY_CATEGORY_BITMASK = 0x06; // 0110
const int ENEMY_COLLISION_BITMASK = 0xFFFFFFFF;

// Enemy bullet can collide with: Player
const int ENEMY_BULLET_CONTACT_TEST_BITMASK = 0x08; // 1000
const int ENEMY_BULLET_CATEGORY_BITMASK = 0x06; // 0110
const int ENEMY_BULLET_COLLISION_BITMASK = 0xFFFFFFFF;

// Player bullet can collide with: Enemy
const int PLAYER_BULLET_CONTACT_TEST_BITMASK = 0x04; // 0100
const int PLAYER_BULLET_CATEGORY_BITMASK = 0x01; // 0001
const int PLAYER_BULLET_COLLISION_BITMASK = 0xFFFFFFFF;


// Bouding Box
const Size BOUNDING_BOX = Size(1200, 1200);


#endif // !__CONSTANT_H__