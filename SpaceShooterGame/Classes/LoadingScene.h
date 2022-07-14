#ifndef __LOADING_SCENE_H__
#define __LOADING_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;

class LoadingScene : public Scene
{
private:
    void handleLoading();
public:
    static Scene* createScene();

    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(LoadingScene);
};

#endif // __LOADING_SCENE_H__
