#include "GameScene.h"
#include "Player.h"
#include "GameManager.h"
#include "Constant.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
    return GameScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in GameScene.cpp\n");
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::initWithPhysics() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // Init game manager
    GameManager::setWorld(this);
    GameManager::start();

    // Init physics
    this->getPhysicsWorld()->setGravity(Vec2::ZERO);
    this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

    // Init mouse event listener
    auto mouseListener = EventListenerMouse::create();
    mouseListener->onMouseDown = [&](Event* event) {
        EventMouse* e = (EventMouse*)event;
        Vec2 location = e->getLocationInView();
        this->player->setIsShooting(true);
    };
    mouseListener->onMouseUp = [&](Event* event) {
        EventMouse* e = (EventMouse*)event;
        Vec2 location = e->getLocationInView();

        this->player->setIsShooting(false);
    };
    mouseListener->onMouseMove = [&](Event* event) {
        EventMouse* e = (EventMouse*)event;
        Vec2 location = e->getLocationInView();

        //Aim to mouse location
        Vec2 aimDirection = location - this->player->getSprite()->getPosition();
        float radian = aimDirection.getAngle(Vec2(0, 1));
        float angle = radian * 180 / M_PI;
        this->player->getSprite()->setRotation(angle);
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

    // Init keyboard event listeners
    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyPressed, this);
    keyboardListener->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

    // Init contact listeners
    this->initContactListener();

    // Init player
    this->player = new Player();
    this->player->getSprite()->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    addChild(this->player->getSprite());
    GameManager::setPlayer(player);

    scheduleUpdate();
    return true;
}

void GameScene::update(float dt) {
    GameManager::update(dt);
}

void GameScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {
    auto player = GameManager::getPlayer();
    auto newDirection = player->getDirection();

    switch (keyCode) {
    case EventKeyboard::KeyCode::KEY_W:
        newDirection.y = 1;
        break;
    case EventKeyboard::KeyCode::KEY_S:
        newDirection.y = -1;
        break;
    case EventKeyboard::KeyCode::KEY_A:
        newDirection.x = -1;
        break;
    case EventKeyboard::KeyCode::KEY_D:
        newDirection.x = 1;
        break;
    default:
        break;
    }

    newDirection.normalize();
    player->setDirection(newDirection);
}

void GameScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {
    auto player = GameManager::getPlayer();
    auto newDirection = player->getDirection();

    switch (keyCode) {
    case EventKeyboard::KeyCode::KEY_W:
    case EventKeyboard::KeyCode::KEY_S:
        newDirection.y = 0;
        break;
    case EventKeyboard::KeyCode::KEY_A:
    case EventKeyboard::KeyCode::KEY_D:
        newDirection.x = 0;
        break;
    default:
        break;
    }

    newDirection.normalize();
    player->setDirection(newDirection);
}

void GameScene::initContactListener() {
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
    contactListener->onContactSeparate = CC_CALLBACK_1(GameScene::onContactSeparate, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
}

bool GameScene::onContactBegin(PhysicsContact& contact) {
    Node* nodeA = contact.getShapeA()->getBody()->getNode();
    Node* nodeB = contact.getShapeB()->getBody()->getNode();

    /*if (nodeA->getTag() == (int)ContactType::EnemyBullet) {
        nodeA->removeFromParentAndCleanup(true);
    }
    else if (nodeB->getTag() == (int)ContactType::EnemyBullet) {
        nodeB->removeFromParentAndCleanup(true);
    }*/

    if (nodeA && nodeB) {
        if (nodeA->getTag() == (int)ContactType::Enemy && nodeB->getTag() == (int)ContactType::PlayerBullet) {
            Entity* entity = GameManager::findEntity((Sprite*)nodeA);
            if (entity) {
                //entity->getSprite()->setVisible(false);
                GameManager::destroyEntity(entity);
            }
        }
        else if (nodeB->getTag() == (int)ContactType::Enemy && nodeA->getTag() == (int)ContactType::PlayerBullet) {
            Entity* entity = GameManager::findEntity((Sprite*)nodeB);
            if (entity) {
                //entity->getSprite()->setVisible(false);
                GameManager::destroyEntity(entity);
            }
        }
    }

    return true;
}

void GameScene::onContactSeparate(PhysicsContact& contact) {
    Node* nodeA = contact.getShapeA()->getBody()->getNode();
    Node* nodeB = contact.getShapeB()->getBody()->getNode();

    /*nodeA->setColor(Color3B::WHITE);
    nodeB->setColor(Color3B::WHITE);*/
}
