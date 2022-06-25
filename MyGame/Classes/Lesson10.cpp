
#include "ui/CocosGUI.h"
#include "Lesson10.h"

USING_NS_CC;

Scene* Lesson10::createScene()
{
    return Lesson10::create();
}

// on "init" you need to initialize your instance
bool Lesson10::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    this->mySprite = Sprite::create("player.png");
    this->mySprite->setPosition(200, 200);
    addChild(mySprite);

    // Init mouse listener
    auto mouseListener = EventListenerMouse::create();
    mouseListener->onMouseDown = CC_CALLBACK_1(Lesson10::onMouseDown, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

    //this->initParticleSystem();

    //this->scheduleUpdate();
    return true;
}


//void Lesson10::update(float dt) {
//    // Handle update game state here
//}

void Lesson10::onMouseDown(Event* event) {
    EventMouse* e = (EventMouse*)event;
    Vec2 location = e->getLocationInView();

    Vec2 direction = location - this->mySprite->getPosition();
    direction.normalize();

    auto bullet = Sprite::create("rocket.png");
    bullet->setPosition(this->mySprite->getPosition());
    bullet->setContentSize(Size(20, 50));
    float radian = direction.getAngle(Vec2(0, 1));
    float angle = radian * 180 / M_PI;
    bullet->setRotation(angle);
    addChild(bullet);
    bullet->runAction(MoveBy::create(5, direction * 1000));

    // apply particle to bullet
    auto particle = ParticleMeteor::create();
    particle->setAngle(angle);
    particle->setGravity(Vec2(0, 0));
    particle->setPosition(Vec2(bullet->getContentSize().width / 2, -1 * (direction * 10).y));
    bullet->addChild(particle);
}

void Lesson10::initParticleSystem() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // Scroll View
    auto scrollView = ui::ScrollView::create();
    scrollView->setAnchorPoint(Vec2(0.5, 0.5));
    scrollView->setPosition(Vec2(visibleSize.width * 0.5, visibleSize.height * 0.5));
    scrollView->setDirection(ui::ScrollView::Direction::VERTICAL);
    //scrollView->setBounceEnabled(true);
    scrollView->setScrollBarColor(Color3B::BLUE);
    addChild(scrollView);
    scrollView->setInnerContainerSize(Size(800, 3000));
    scrollView->setContentSize(Size(800, 600));

    auto my_particle = ParticleSystemQuad::create("particles/particle_texture.plist");
    my_particle->setPosition(400, 2600);
    scrollView->addChild(my_particle);

    vector<ParticleSystem*> particles = {
        ParticleRain::create(),
        ParticleExplosion::create(),
        ParticleFire::create(),
        ParticleFireworks::create(),
        ParticleSun::create(),
        ParticleGalaxy::create(),
        ParticleFlower::create(),
        ParticleMeteor::create(),
        ParticleSpiral::create(),
        ParticleSmoke::create(),
        ParticleSnow::create(),
    };

    for (int i = 0; i < particles.size(); i++) {
        particles[i]->setPosition(i%2 * 400 + 200, int(i/2) * (-400) + 2200);

        particles[i]->setEmitterMode(ParticleSystem::Mode::GRAVITY);
        particles[i]->setAngle(45);
        //particles[i]->setDuration(5);
        particles[i]->setStartColor(Color4F(0.1, 0.5, 1, 1));
        particles[i]->setEndColor(Color4F(1, 0.1, 0.1, 0.8));
        //particles[i]->setGravity(Vec2(0, -300)); // Work with Gravity mode
        //particles[i]->setStartRadius(50); // work with Radius mode
        //particles[i]->setEndRadius(200); // work with Radius mode

        scrollView->addChild(particles[i]);
    }
}
