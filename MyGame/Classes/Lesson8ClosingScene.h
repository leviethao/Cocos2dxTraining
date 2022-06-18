#ifndef __LESSON8_CLOSING_SCENE_H__
#define __LESSON8_CLOSING_SCENE_H__

#include "cocos2d.h"

class Lesson8ClosingScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene(int score);

    virtual bool init();
    //void update(float dt);

    void initUI();

    // implement the "static create()" method manually
    CREATE_FUNC(Lesson8ClosingScene);
    
};

#endif // __LESSON8_Closing_SCENE_H__
