#ifndef __LESSON5_H__
#define __LESSON5_H__

#include "cocos2d.h"

class Lesson5 : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    void update(float dt);

private:
    cocos2d::Sprite* mySprite;
    cocos2d::Sprite* mySprite2;
    void onMouseDown(cocos2d::Event* event);

    // When collision ended
    void onContactSeparate(cocos2d::PhysicsContact& contact);
    
    // Init contact listener
    void initContactListener();

    // implement the "static create()" method manually
    CREATE_FUNC(Lesson5);
    
};

#endif // __LESSON5_H__
