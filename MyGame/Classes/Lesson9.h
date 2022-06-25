#ifndef __LESSON9_H__
#define __LESSON9_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

using namespace std;

class Lesson9 : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    //void update(float dt);
    void onMouseDown(cocos2d::Event* event);

    cocos2d::Sprite* mySprite;


    int backgroundMusic; // audio id


    cocos2d::Label* soundLabel;

    void initAnimation();

    cocos2d::Animation* createAnimation(string prefixName, int pFramesOrder, float delay);
    
    cocos2d::Animation* animation;


    void run();
    // implement the "static create()" method manually
    CREATE_FUNC(Lesson9);
    
};

#endif // __LESSON9_H__
