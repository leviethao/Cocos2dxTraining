#ifndef __LESSON4_CONTINUE_H__
#define __LESSON4_CONTINUE_H__

#include "cocos2d.h"

class Lesson4Continue : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    void update(float dt);

private:
    cocos2d::Sprite* mySprite;
    cocos2d::Sprite* mySprite2;
    void onMouseDown(cocos2d::Event* event);
    void onMouseUp(cocos2d::Event* event);
    void onMouseMove(cocos2d::Event* event);

    // Variable for mouse move (move sprite)
    cocos2d::Vec2 mouseLoc;
    cocos2d::Vec2 direction;
    float speed;
    bool isKeyDown = false;
    bool isDragDrop = false;

    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event);

    void shootingBullet(cocos2d::Vec2 targetPos);

    // a selector callback
    //void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(Lesson4Continue);
    
};

#endif // __LESSON4_CONTINUE_H__
