#ifndef __LESSON10_H__
#define __LESSON10_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

using namespace std;

class Lesson10 : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    //void update(float dt);
    void onMouseDown(cocos2d::Event* event);

    cocos2d::Sprite* mySprite;

    void initParticleSystem();

    // implement the "static create()" method manually
    CREATE_FUNC(Lesson10);
    
};

#endif // __LESSON10_H__
