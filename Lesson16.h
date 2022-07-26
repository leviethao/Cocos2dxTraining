#ifndef __LESSON16_H__
#define __LESSON16_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

using namespace std;

class Lesson16 : public cocos2d::Scene
{
private:
    cocos2d::Sprite* mySprite;
    float speed;
    cocos2d::Vec2 direction;

    void onMouseDown(cocos2d::Event* event);
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    void update(float dt);


    // implement the "static create()" method manually
    CREATE_FUNC(Lesson16);
    
};

#endif // __LESSON15_H__
