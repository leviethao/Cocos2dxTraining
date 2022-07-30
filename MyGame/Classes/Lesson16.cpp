
#include "ui/CocosGUI.h"
#include "Lesson16.h"
#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"
#include <time.h>


USING_NS_CC;


const char* GetJsonText(rapidjson::Document& doc)
{
	rapidjson::StringBuffer buffer;
	buffer.Clear();
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	doc.Accept(writer);
	return strdup(buffer.GetString());
}

rapidjson::Document createEventData(const std::string& playerName, float positionX, float positionY) {
	rapidjson::Document document;
	document.SetObject();

	document.AddMember(rapidjson::Value("playerName", document.GetAllocator()),
		rapidjson::Value(playerName.c_str(), document.GetAllocator()), document.GetAllocator());

	document.AddMember(rapidjson::Value().SetString("positionX"),
		rapidjson::Value().SetFloat(positionX), document.GetAllocator());

	document.AddMember(rapidjson::Value().SetString("positionY"),
		rapidjson::Value().SetFloat(positionY), document.GetAllocator());

	//document["playerName"] = "abc"; // Change value of key playerName
	return document;
}



Scene* Lesson16::createScene()
{
    return Lesson16::create();
}

// on "init" you need to initialize your instance
bool Lesson16::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


	// Init mouse listener
	auto mouseListener = EventListenerMouse::create();
	mouseListener->onMouseDown = CC_CALLBACK_1(Lesson16::onMouseDown, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

	// Init keyboard listener
	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(Lesson16::onKeyPressed, this);
	keyboardListener->onKeyReleased = CC_CALLBACK_2(Lesson16::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

	// connect to server
	_client = network::SocketIO::connect("http://127.0.0.1:3000", *this);
	_client->on("friendMove", CC_CALLBACK_2(Lesson16::onFriendMove, this));

	//
	this->mySprite = Sprite::create("player.png");
	this->mySprite->setPosition(200, 200);
	srand(time(NULL));
	this->mySprite->setName(std::to_string(rand() % 10000));
	addChild(mySprite);
	this->playerList.push_back(this->mySprite);

	this->direction = Vec2::ZERO;
	this->speed = 200;

	schedule([&](float dt) {
		rapidjson::Document jsonData = createEventData(mySprite->getName(), mySprite->getPosition().x,
			mySprite->getPosition().y);
		const char* strJsonData = GetJsonText(jsonData);
		_client->emit("updateLocation", strJsonData);
		}, 1 / 15, "UpdateLocation");


    this->scheduleUpdate();
    
	return true;
}


void Lesson16::update(float dt) {
    // Handle update game state here

	this->mySprite->setPosition(mySprite->getPosition() + this->speed * dt * this->direction);
}


void Lesson16::onMouseDown(Event* event) {
    EventMouse* e = (EventMouse*)event;
    Vec2 location = e->getLocationInView();

    Vec2 direction = location - this->mySprite->getPosition();
    direction.normalize();
}



void Lesson16::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {
	auto newDirection = direction;

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
	this->direction = newDirection;
}

void Lesson16::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {
	auto newDirection = direction;

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
	this->direction = newDirection;
}



void Lesson16::onConnect(cocos2d::network::SIOClient* client) {
	// SocketIO::connect success
	log("SocketIO connect sucess!");
	_client->emit("message", "User001 connect success");
}
void Lesson16::onMessage(cocos2d::network::SIOClient* client, const std::string& data) {
	// SocketIO::send receive
	log("On Message: data from socket server: %s", data.c_str());
	//_client->emit("message", "User001 reply message");
}
void Lesson16::onClose(cocos2d::network::SIOClient* client) {
	// SocketIO::disconnect success
	log("On Close: socket disconnect success");
}
void Lesson16::onError(cocos2d::network::SIOClient* client, const std::string& data) {
	// SocketIO::failed
	log("On Error: socket failed!");
}



void Lesson16::onFriendMove(cocos2d::network::SIOClient* client, const std::string& data) {
	rapidjson::Document jsonData;
	jsonData.Parse(data.c_str());
	if (jsonData.IsObject() == false) return;

	const char* friendName = jsonData["playerName"].GetString();
	/*log("MySpriteName: %s,   FriendName: %s", mySprite->getName().c_str(), friendName);*/
	if (std::string(friendName) == mySprite->getName()) return;

	for (cocos2d::Sprite* player : this->playerList) {
		auto found = std::find_if(playerList.begin(), playerList.end(), [&](Sprite* sprite) {
			return sprite->getName() == std::string(friendName);
			});

		Vec2 newPosition = Vec2(jsonData["positionX"].GetFloat(),
			jsonData["positionY"].GetFloat());

		if (found != playerList.end()) {
			// old friend
			/*(*found)->stopAllActions();
			(*found)->runAction(MoveTo::create(0.1, newPosition));*/
			(*found)->setPosition(newPosition);
		}
		else {
			// new friend
			cocos2d::Sprite* newFriend = Sprite::create("player.png");
			int r = rand() * (255 - 20 + 1) + 20;
			int g = rand() * (255 - 20 + 1) + 20;
			int b = rand() * (255 - 20 + 1) + 20;
			newFriend->setColor(Color3B(r, g, b));
			newFriend->setPosition(newPosition);
			newFriend->setName(friendName);
			addChild(newFriend);
			this->playerList.push_back(newFriend);
		}
	}
}