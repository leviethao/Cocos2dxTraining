#ifndef __LESSON4_H__
#define __LESSON4_H__

#include "cocos2d.h"

class Lesson4 : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    void update(float dt);

private:
    cocos2d::Sprite* mySprite;
    void onMouseDown(cocos2d::Event* event);
    void onMouseMove(cocos2d::Event* event);

    // Variable for mouse move (move sprite)
    cocos2d::Vec2 mouseLoc;
    cocos2d::Vec2 direction;
    float speed;

    // a selector callback
    //void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(Lesson4);
    
};

#endif // __LESSON4_H__
