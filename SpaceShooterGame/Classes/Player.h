#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "cocos2d.h"
#include "Entity.h"
#include "Bullet.h"
#include "GunLV2.h"
#include "BulletPool.h"
#include "network/SocketIO.h"

USING_NS_CC;

class Player : public Entity, public network::SocketIO::SIODelegate
{
private:
	BulletPool* bulletPool;
	Bullet* bullet;
	std::vector<GunLV2*> guns;

	float exp;
	float level;
	int heart;

	network::SIOClient* _client;

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
	void scheduleShooting(float dt);


	// socket.io even\vent listener
	void onReceiveEvent(network::SIOClient* client, const std::string& data);
	// SIODelegate
	virtual void onConnect(network::SIOClient* client);
	virtual void onMessage(network::SIOClient* client, const std::string& data);
	virtual void onClose(network::SIOClient* client);
	virtual void onError(network::SIOClient* client, const std::string& data);
};

#endif // __PLAYER_H__
