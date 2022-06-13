#ifndef __LESSON6_H__
#define __LESSON6_H__

#include "cocos2d.h"

class Lesson6 : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    void update(float dt);

private:
    cocos2d::Sprite* mySprite;
    cocos2d::Sprite* mySprite2;
    cocos2d::Sprite* mySprite3;
    void onMouseDown(cocos2d::Event* event);

    void initPhysics();

    // implement the "static create()" method manually
    CREATE_FUNC(Lesson6);
    
};

#endif // __LESSON6_H__
