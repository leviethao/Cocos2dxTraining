#include "GameScene.h"
#include "Player.h"
#include "GameManager.h"
#include "Constant.h"
#include "ui/CocosGUI.h"

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

    // Init contact listeners
    this->initContactListener();

    // Init player
    this->player = new Player();
    this->player->getSprite()->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    this->player->getSprite()->setLocalZOrder(1);
    GameManager::addEntity(player);
    GameManager::setPlayer(player);

    // Camera
    this->initCameraUI();

    // GUI
    this->initBackground();
    this->initPauseMenu();
    this->initPlayerInfoUI();

    scheduleUpdate();
    return true;
}

void GameScene::update(float dt) {
    this->updatePlayerInfo();

    this->followPlayer();
    GameManager::update(dt);
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

    if (nodeA && nodeB) {
        /*nodeA->setColor(Color3B::BLACK);
        nodeB->setColor(Color3B::BLACK);*/

        Entity* entityA = GameManager::findEntity((Sprite*)nodeA);
        Entity* entityB = GameManager::findEntity((Sprite*)nodeB);
        float damageA = entityA->getDamage();
        float damageB = entityB->getDamage();
        entityA->takeDamage(damageB);
        entityB->takeDamage(damageA);
    }

    return true;
}

void GameScene::onContactSeparate(PhysicsContact& contact) {
    Node* nodeA = contact.getShapeA()->getBody()->getNode();
    Node* nodeB = contact.getShapeB()->getBody()->getNode();

    /*nodeA->setColor(Color3B::WHITE);
    nodeB->setColor(Color3B::WHITE);*/
}


void GameScene::initPlayerInfoUI() {
    this->playerInfo = Node::create();
    playerInfo->setAnchorPoint(Vec2(0, 0.5));

    // HP
    Sprite* hpBarBG = Sprite::create("hpBarBG.png");
    hpBarBG->setName("hpBarBG");
    hpBarBG->setContentSize(Size(200, 20));
    hpBarBG->setAnchorPoint(Vec2(0, 0.5));

    Sprite* hpBar = Sprite::create("hpBar.png");
    hpBar->setName("hpBar");
    hpBar->setContentSize(Size(200, 20));
    hpBar->setAnchorPoint(Vec2(0, 0.5));

    playerInfo->addChild(hpBarBG);
    playerInfo->addChild(hpBar);

    // Heart: Heart Count & Heart Icon
    Node* heart = Node::create();
    heart->setName("heart");
    heart->setAnchorPoint(Vec2(0, 0.5));

    Label* heartLabel = Label::createWithTTF("5", "fonts/Marker Felt.ttf", 20);
    heartLabel->setName("heartLabel");
    heartLabel->setAnchorPoint(Vec2(0, 0.5));

    Sprite* heartIcon = Sprite::create("heart.png");
    heartIcon->setContentSize(Size(20, 20));
    heartIcon->setAnchorPoint(Vec2(0, 0.5));
    const float padding = 8;
    heartIcon->setPosition(Vec2(heartLabel->getContentSize().width + padding, 0));

    heart->addChild(heartLabel);
    heart->addChild(heartIcon);

    heart->setPosition(Vec2(hpBarBG->getContentSize().width + 16, 0));
    playerInfo->addChild(heart);

    addChild(playerInfo);
    playerInfo->setPosition(Vec2(50, 50) - GameManager::getVisibleSize() / 2);

    playerInfo->setCameraMask((unsigned short)this->cameraUI->getCameraFlag());
}

void GameScene::updatePlayerInfo() {
    auto hpBarBG = this->playerInfo->getChildByName("hpBarBG");
    auto hpBar = this->playerInfo->getChildByName("hpBar");
    auto heartLabel = this->playerInfo->getChildByName("heart")->getChildByName("heartLabel");

    const Size hpBarMaxSize = hpBarBG->getContentSize();
    Size hpBarSize = hpBarMaxSize;
    hpBarSize.width = this->player->getHP() / this->player->getMaxHP() * hpBarMaxSize.width;
    hpBar->setContentSize(hpBarSize);

    ((Label*)heartLabel)->setString(std::to_string(this->player->getHeart()));
}

void GameScene::initPauseMenu() {
    ui::Button* btnPause = ui::Button::create("btnPauseNormal.png", "btnPauseSelected.png", "btnPauseNormal.png");
    btnPause->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
        switch (type) {
        case ui::Widget::TouchEventType::BEGAN:
            break;
        case ui::Widget::TouchEventType::ENDED:
            log("Pressed");
            GameManager::pause();
            scheduleOnce([](float dt) {
                GameManager::resume();
            }, 3, "resumeGame");
            break;
        default:
            break;
        }
    });

    float factor = 30; //GameManager::getVisibleSize().width / 16;
    float xscale = factor / btnPause->getContentSize().width;
    float yscale = factor / btnPause->getContentSize().height;
    btnPause->setScale(xscale, yscale);
    btnPause->setPosition(Vec2(50, GameManager::getVisibleSize().height - 50) - GameManager::getVisibleSize() / 2);
    addChild(btnPause);
    btnPause->setCameraMask((unsigned int)this->cameraUI->getCameraFlag());

    /*auto followPlayer = Follow::create(player->getSprite(), Rect(0,
        0, 1600, 1200));
    runAction(followPlayer);*/
}

void GameScene::followPlayer() {
    auto camera = getDefaultCamera();
    auto targetPos = player->getSprite()->getPosition();
    auto visibleSize = GameManager::getVisibleSize();
    targetPos.x = clampf(targetPos.x, visibleSize.width / 2 - (BOUNDING_BOX.width - visibleSize.width) / 2,
        visibleSize.width / 2 + (BOUNDING_BOX.width - visibleSize.width) / 2);
    targetPos.y = clampf(targetPos.y, visibleSize.height / 2 - (BOUNDING_BOX.height - visibleSize.height) / 2,
        visibleSize.height / 2 + (BOUNDING_BOX.height - visibleSize.height) / 2);
    auto curPos = camera->getPosition();
    curPos = curPos.lerp(targetPos, 0.1);
    camera->setPosition(curPos);
}

void GameScene::initCameraUI() {
    this->cameraUI = Camera::create();
    this->cameraUI->setCameraFlag(CameraFlag::USER1);
    addChild(this->cameraUI);

    Vec3 eyePosOld = this->cameraUI->getPosition3D();
    this->cameraUI->setPosition3D(Vec3(0, 0, eyePosOld.z));
    this->cameraUI->lookAt(Vec3(0, 0, 0));
}

void GameScene::initBackground() {
    auto boundingBoxBorderLayer = LayerColor::create(Color4B(10, 10, 100, 255));
    boundingBoxBorderLayer->setContentSize(BOUNDING_BOX);
    boundingBoxBorderLayer->setPosition((boundingBoxBorderLayer->getContentSize() - GameManager::getVisibleSize()) / 2 * -1);
    addChild(boundingBoxBorderLayer);

    auto boundingBoxInnerLayer = LayerColor::create(Color4B(10, 100, 10, 255));
    boundingBoxInnerLayer->setContentSize(BOUNDING_BOX - Size(20, 20));
    boundingBoxInnerLayer->setPosition((boundingBoxInnerLayer->getContentSize() - GameManager::getVisibleSize()) / 2 * -1);
    addChild(boundingBoxInnerLayer);

    auto windowLayer = LayerColor::create(Color4B(100, 10, 10, 255));
    windowLayer->setContentSize(GameManager::getVisibleSize());
    addChild(windowLayer);
}
