#ifndef __LESSON16_H__
#define __LESSON16_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

#include "network/SocketIO.h"

using namespace std;

class Lesson16 : public cocos2d::Scene, public cocos2d::network::SocketIO::SIODelegate
{
private:
    cocos2d::network::SIOClient* _client;
    cocos2d::Sprite* mySprite;
    float speed;
    cocos2d::Vec2 direction;
    std::vector<cocos2d::Sprite*> playerList;

    void onMouseDown(cocos2d::Event* event);
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    void update(float dt);


    // SIODelegate
    virtual void onConnect(cocos2d::network::SIOClient* client);
    virtual void onMessage(cocos2d::network::SIOClient* client, const std::string& data);
    virtual void onClose(cocos2d::network::SIOClient* client);
    virtual void onError(cocos2d::network::SIOClient* client, const std::string& data);
    
    virtual void onFriendMove(cocos2d::network::SIOClient* client, const std::string& data);

    // implement the "static create()" method manually
    CREATE_FUNC(Lesson16);
    
};

#endif // __LESSON15_H__
