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

#include "HelloWorldScene.h"
#include <iostream>
using namespace std;

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}


// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
   
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    //auto dog = Sprite::create("dog.png", Rect(0, 0, 512, 512));
    //dog->setPosition(Vec2(0, 0));
    //dog->setAnchorPoint(Vec2(0, 0));
    //dog->setContentSize(Size(200, 200));
    ////dog->setScaleX(0.5);
    ////dog->setRotation(45);
    //addChild(dog);
    ////dog->setContentSize(Size(visibleSize.width, visibleSize.height));
    ////dog->setSkewX(20);
    ////dog->setColor(Color3B(255, 255, 255));

    //auto dog2 = Sprite::create("dog.png");
    //addChild(dog2);
    //dog2->setPosition(Vec2(150, 100));
    //dog2->setAnchorPoint(Vec2(0, 0));
    //dog2->setContentSize(Size(100, 100));
    ////dog2->setSkewX(20);
    //dog2->setOpacity(100);
    ///*dog2->getPosition()*/

    //float x = dog->getPosition().x + dog->getContentSize().width;
    //float y = dog->getPosition().y + dog->getContentSize().height;
    //dog2->setPosition(Vec2(x, y));
    //CCLOG("value = %i", 10);

    float width = visibleSize.width / 6;
    float height = visibleSize.height / 4;

    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 4; j++) {
            auto dog = Sprite::create("dog.png");
            addChild(dog);
            dog->setContentSize(Size(width, height));
            dog->setAnchorPoint(Vec2(0, 0));
            float x = i * width;
            float y = j * height;
            dog->setPosition(Vec2(x, y));
        }
    }

    return true;
}
