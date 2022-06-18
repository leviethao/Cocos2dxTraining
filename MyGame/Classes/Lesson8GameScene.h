#ifndef __LESSON8_GAME_SCENE_H__
#define __LESSON8_GAME_SCENE_H__

#include "cocos2d.h"

class Lesson8GameScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    //void update(float dt);

    void onMouseDown(cocos2d::Event* event);

    void initUI();

    // implement the "static create()" method manually
    CREATE_FUNC(Lesson8GameScene);
    
};

#endif // __LESSON8_GAME_SCENE_H__
