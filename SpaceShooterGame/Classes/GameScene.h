#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "Player.h"

class GameScene : public cocos2d::Scene
{
private:
    Player* player;
    Node* playerInfo;
    Camera* cameraUI;

    bool onContactBegin(PhysicsContact& contact);
    void onContactSeparate(PhysicsContact& contact);
    void initContactListener();
    void initPlayerInfoUI();
    void updatePlayerInfo();
    void initPauseMenu();
    void followPlayer();
    void initCameraUI();
    void initBackground();
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    void update(float dt);

    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
};

#endif // __GAME_SCENE_H__
