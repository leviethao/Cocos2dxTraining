#ifndef __LESSON8_INTRO_SCENE_H__
#define __LESSON8_INTRO_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class Lesson8IntroScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    //void update(float dt);
    void onMouseDown(cocos2d::Event* event);

    cocos2d::Sprite* mySprite;
    cocos2d::SpriteFrameCache* cache;
    cocos2d::ui::LoadingBar* loadingBar;

    void initUI();
    void allTexturesLoaded(cocos2d::Texture2D* texture);

    // implement the "static create()" method manually
    CREATE_FUNC(Lesson8IntroScene);
    
};

#endif // __LESSON8_INTRO_SCENE_H__
