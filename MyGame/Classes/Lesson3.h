#ifndef __LESSON3_H__
#define __LESSON3_H__

#include "cocos2d.h"

class Lesson3 : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    void update(float dt);

private:
    cocos2d::Sprite* mySprite;
    // a selector callback
    //void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(Lesson3);
    
};

#endif // __LESSON3_H__
