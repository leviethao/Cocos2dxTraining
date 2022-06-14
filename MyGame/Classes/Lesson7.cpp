
#include "Lesson7.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

Scene* Lesson7::createScene()
{
    return Lesson7::create();
}

// on "init" you need to initialize your instance
bool Lesson7::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    this->initUI();

    //this->scheduleUpdate();
    return true;
}


void Lesson7::initUI() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // Create backgroud
    /*LayerColor* background = LayerColor::create(Color4B(255, 255, 255, 255));
    addChild(background);*/
    //background->setPosition(Vec2(-100, -100));

    // Create TTF Label
    auto myLabel = Label::createWithTTF("My Text", "fonts/Marker Felt.ttf", 24);
    myLabel->setTextColor(Color4B(255, 255, 255, 100));
    myLabel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.8));
    myLabel->enableShadow(Color4B::YELLOW);
    myLabel->enableOutline(Color4B(255, 0, 0, 255), 1);
    myLabel->enableGlow(Color4B(200, 20, 0, 255));
    addChild(myLabel);



    // Create Button
    auto button = ui::Button::create("button-normal.png", "button-selected.png", "button-disabled.png");
    button->setPosition(Vec2(visibleSize.width * 0.2, visibleSize.height * 0.8));
    //button->setBright(false); // to disabled

    /*button->setTitleText("HIHI");
    button->setTitleColor(Color3B::RED);*/
    addChild(button);

    // Add button touch event
    button->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
        switch (type)
        {
        case ui::Widget::TouchEventType::BEGAN:
            break;
        case ui::Widget::TouchEventType::ENDED:
            CCLOG("Pressed");
            break;
        default:
            break;
        }
    });

    // Text Field
    auto textField = ui::TextField::create("Input some thing", "Arial", 30);
    textField->addEventListener([&](Ref* sender, ui::TextField::EventType type) {
        auto _textField = dynamic_cast<ui::TextField*>(sender);
        switch (type) {
        case ui::TextField::EventType::ATTACH_WITH_IME:
            CCLOG("Focus");
            break;
        case ui::TextField::EventType::DETACH_WITH_IME:
            CCLOG("Blur");
            break;
        case ui::TextField::EventType::INSERT_TEXT:
            CCLOG("Inserted text: %s", _textField->getString().c_str());
            break;
        case ui::TextField::EventType::DELETE_BACKWARD:
            CCLOG("Deleted backward");
            break;
        default:
            break;
        }
        CCLOG("editing textfield");
    });
    textField->setPlaceHolderColor(Color4B::BLACK);
    textField->setTextColor(Color4B::BLACK);
    textField->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.6));
    //textField->setMaxLength(10);
    //textField->setPasswordEnabled(true);
    addChild(textField);


    // Menu
    Vector<MenuItem*> menuItems = {
        MenuItemLabel::create(Label::createWithSystemFont("Settings", "Arial", 20)  , [&](Ref* sender) {
            CCLOG("Settings");
        }),
        MenuItemLabel::create(Label::createWithSystemFont("Quit", "Arial", 20), [&](Ref* sender) {
            CCLOG("Quit");
        }),
        MenuItemImage::create("button-normal.png", "button-selected.png", [&](Ref* sender) {
            /*auto node = dynamic_cast<Node*>(sender);
            node->getTag();*/
            CCLOG("Play Game");
        }),
    };

    auto menu = Menu::createWithArray(menuItems);
    addChild(menu);
    menu->alignItemsVertically();
    menu->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));


    // Loading Bar Background
    auto loadingBarBG = Sprite::create("loadingBarBG.png");
    loadingBarBG->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.3));
    addChild(loadingBarBG);

    //Loading Bar
    auto loadingBar = ui::LoadingBar::create("loadingBar.png");
    loadingBar->setPosition(loadingBarBG->getPosition());
    loadingBar->setDirection(ui::LoadingBar::Direction::LEFT);
    loadingBar->setPercent(30);
    this->addChild(loadingBar);
    this->schedule([=](float delta) {
        float percent = loadingBar->getPercent();
        percent++;
        loadingBar->setPercent(percent);
        if (percent >= 100) {
            this->unschedule("updateLoadingBar");
        }
    }, 0.1, "updateLoadingBar");


    // Slider
    auto slider = ui::Slider::create("loadingBarBG.png", "slider2.png");
    slider->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.2));
    addChild(slider);
    slider->addEventListener([](Ref* sender, ui::Slider::EventType type) {
        auto slider = dynamic_cast<ui::Slider*>(sender);
        if (type == ui::Slider::EventType::ON_PERCENTAGE_CHANGED) {
            CCLOG("%d", slider->getPercent());
        }
    });

    // Scroll View
    auto scrollView = ui::ScrollView::create();
    scrollView->setPosition(Vec2(visibleSize.width * 0.5, visibleSize.height * 0.5));
    scrollView->setDirection(ui::ScrollView::Direction::BOTH);
    //scrollView->setBounceEnabled(true);
    scrollView->setColor(Color3B::RED);
    addChild(scrollView);

    auto sprite = Sprite::create("scrollviewItem.jpg");
    //sprite->setScale(10);
    sprite->setContentSize(Size(1000, 1000));
    sprite->setPosition(sprite->getContentSize() / 2);
    scrollView->addChild(sprite);
    /*scrollView->setInnerContainerSize(sprite->getBoundingBox().size);
    scrollView->setContentSize(sprite->getContentSize() * 0.6);*/
    scrollView->setInnerContainerSize(Size(1000, 1000));
    scrollView->setContentSize(Size(500, 500));

    scrollView->setBackGroundColor(Color3B::RED);

}