/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#ifndef __LESSON21_H__
#define __LESSON21_H__

#include "cocos2d.h"


class Player {
public:
    cocos2d::Sprite* sprite;
    cocos2d::PhysicsBody* body;
    cocos2d::Vec2 direction;
    float jumpFac;

    Player();
    ~Player();

    void jump();

    void move();
};

class Lesson21 : public cocos2d::Scene
{
private:
    cocos2d::ParallaxNode* parallaxNode;
    std::vector<cocos2d::Sprite*> frontList;
    std::vector<cocos2d::Sprite*> backList;
    cocos2d::Vec2 startPos;

    float backgroundSpeed;
    cocos2d::Vec2 backgroundDirection;

    Player* player;

    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void scrollParallax(float delta, std::vector<cocos2d::Sprite*> &list);
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    void update(float dt);
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(Lesson21);
};

#endif // __LESSON21_H__
