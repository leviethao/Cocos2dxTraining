#ifndef __LESSON7_H__
#define __LESSON7_H__

#include "cocos2d.h"

class Lesson7 : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    //void update(float dt);

    void initUI();

    // implement the "static create()" method manually
    CREATE_FUNC(Lesson7);
    
};

#endif // __TEST7_H__
