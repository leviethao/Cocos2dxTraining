#include "Player.h"
#include "Bullet.h"
#include "GameManager.h"
#include "network/HttpClient.h"

#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"

#include "SQLite/sqlite3.h"

USING_NS_CC;

Player::Player(): Entity("Player.png") {
	this->body->setContactTestBitmask(PLAYER_CONTACT_TEST_BITMASK);
	this->body->setCategoryBitmask(PLAYER_CATEGORY_BITMASK);
	this->body->setCollisionBitmask(PLAYER_COLLISION_BITMASK);

	this->init();




	// connect to server
	/*_client = network::SocketIO::connect("http://127.0.0.1:3001", *this);
	_client->on("message", CC_CALLBACK_2(Player::onReceiveEvent, this));*/
}

Player::~Player() {

}

void Player::init()
{
	this->setMaxHP(100);
	this->setHP(100);
	this->damage = 100;
	this->heart = 1;
	this->level = 1;
	this->setSpeed(300);

	this->initEventListener();
}

void Player::shooting() {
	auto aimAngle = this->sprite->getRotation() * -1;
	Vec2 aimDirection = Vec2(0, 1);
	aimDirection.rotate(Vec2(0, 0), aimAngle * M_PI / 180);
	aimDirection.normalize();
	
	this->bullet = new Bullet(ContactType::PlayerBullet);
	this->bullet->init();
	Sprite* sBullet = bullet->getSprite();
	//sBullet->setContentSize(Size(20, 30));
	sBullet->setPosition(this->sprite->getPosition() + aimDirection * 10);
	float radian = aimDirection.getAngle(Vec2(0, 1));
	float angle = radian * 180 / M_PI;
	sBullet->setRotation(angle);
	bullet->setSpeed(400);
	bullet->setDirection(aimDirection);
	GameManager::addEntity(bullet);

	// Shooting guns
	for (GunLV2* gun : this->guns) {
		gun->shooting();
	}
}

void Player::setIsShooting(bool isShooting) {
	if (isShooting) {
		// Shooting first bullet
		this->shooting();

		// Schedule shooting
		this->sprite->schedule([&](float dt) {
			this->shooting();
		}, 0.1, "PlayerShooting");
	}
	else {
		this->sprite->unschedule("PlayerShooting");
	}
}

void Player::takeDamage(float damage) {
	this->hp -= damage;
	if (this->hp <= 0) {
		if (this->heart > 0) {
			this->heart--;
			this->hp = this->maxHP;
		}
		else {
			this->hp = 0;
		}
	}
}

int Player::getHeart() {
	return this->heart;
}

void Player::setHeart(int heart) {
	this->heart = heart;
}

void Player::die() {
	auto node = Node::create();
	node->scheduleOnce([&](float dt) {
		GameManager::end();
	}, 5, "EndGame");
	GameManager::getWorld()->addChild(node);
	
	this->pause();
}

void Player::update(float dt) {
	// Super update
	Entity::update(dt);

	if (this->hp <= 0) {
		//this->die();
	}
}

void Player::initEventListener() {
	// Init mouse event listener
	auto mouseListener = EventListenerMouse::create();
	mouseListener->onMouseDown = [&](Event* event) {
		EventMouse* e = (EventMouse*)event;
		Vec2 location = e->getLocationInView();
		this->setIsShooting(true);

		// Network
		network::HttpRequest* request = new (std::nothrow) network::HttpRequest();
		request->setUrl("http://localhost:3000/updatePlayer");
		request->setRequestType(network::HttpRequest::Type::POST);
		std::string strData = "level=2&score=100&skin=normal";
		request->setRequestData(strData.c_str(), strData.length());
		std::vector<std::string> headers;
		headers.push_back("Content-Type: application/x-www-form-urlencoded");
		request->setHeaders(headers);
		request->setResponseCallback([&](network::HttpClient* sender, network::HttpResponse* response) {
			if (!response) return;

			// Dump the data
			std::vector<char>* buffer = response->getResponseData();
			std::string ret(buffer->begin(), buffer->end());
			//log("response data: %s", ret.c_str());



			// Parse Json data
			/*rapidjson::Document d;
			d.Parse(ret.c_str());
			rapidjson::Value& a = d["keyA"];
			std::string va = a.GetString();
			log("va = %s", va.c_str());
			log("vb = %d", d["keyB"].GetInt());
			log("vd = %s", d["keyC"]["keyD"].GetBool() ? "TRUE" : "FALSE");*/
		
			



			// Parse Image base64, show image on scene
			//std::string base64Image = "iVBORw0KGgoAAAANSUhEUgAAAp0AAAIfLkc/n532tXB/f92uF2DjwRcwvEpWq8/7suQmCC...";
			/*unsigned char* buff;
			int len = base64Decode((unsigned char*)ret.c_str(), ret.length(), &buff);

			auto img = new Image();
			img->initWithImageData(buff, len);
			auto texture = new Texture2D();
			texture->initWithImage(img);

			auto sprite = Sprite::createWithTexture(texture);
			sprite->setPosition(100, 100);
			sprite->setGlobalZOrder(2);
			GameManager::getWorld()->addChild(sprite);*/
			
		});

		network::HttpClient::getInstance()->sendImmediate(request);

		request->release();




		//SQLite
		sqlite3* db = NULL;
		std::string dbPath = FileUtils::getInstance()->getWritablePath() + "myDatabase.db";
		int result = sqlite3_open(dbPath.c_str(), &db);
		if (result == SQLITE_OK) {
			log("open database successful, dbPath: %s", dbPath.c_str());
			
			// Create Table
			result = 0;
			std::string sql;
			sql = "create table " +
			std::string("Master") +
			std::string(" (id TEXT PRIMARY KEY, value INT);");
			result = sqlite3_exec(db, sql.c_str(), NULL, NULL, NULL);
			if (result == SQLITE_OK) {
				log("create table Master successfuly");
			}
			else {
				log("create talbe Master failed");
			}
			//

			// Select
			std::string key = "User003";

			sql = "SELECT value " +
			std::string(" FROM ") +
			std::string("Master") +
			std::string(" WHERE id='") +
			std::string(key.c_str()) +
			std::string("' LIMIT 1;");

			sql = "select value from Master where id='User003';";

			sqlite3_stmt* statement;
			if (sqlite3_prepare_v2(db, sql.c_str(), -1, &statement, 0) == SQLITE_OK)
			{
				int result = 0;

				while (true)
				{
					result = sqlite3_step(statement);

					if (result == SQLITE_ROW)
					{
						// do something with the row.
						//Log for select all 
						const unsigned char* id = sqlite3_column_text(statement, 0);
						int value = sqlite3_column_int(statement, 1);
						log("id = %s, value = %d", id, value);

						// Log for Select by id
						//const unsigned char* id = sqlite3_column_text(statement, 0);
						//log("id = %s",id);
					}
					else
					{
						log("Result not found");
						break;
					}
				}
			}
			//


			// Insert
			std::string id = "User002";
			int value = 10;
			sql = "INSERT INTO " +
			std::string("Master ") +
			std::string("VALUES (") +
			std::string(id.c_str()) +
			std::string(", ") +
			std::to_string(value) +	
			std::string(");");

			sql = "insert into Master (id, value) values ('User003', 13)";
			char* err;
			result = sqlite3_exec(db, sql.c_str(), NULL, NULL, &err);
			if (result == SQLITE_OK) {
				log("Insert success");
			}
			else {
				log("Insert failed");
			}

		}
		else {
			log("open database failed");
		}

	};
	mouseListener->onMouseUp = [&](Event* event) {
		EventMouse* e = (EventMouse*)event;
		Vec2 location = e->getLocationInView();

		this->setIsShooting(false);
	};
	mouseListener->onMouseMove = [&](Event* event) {
		EventMouse* e = (EventMouse*)event;
		Vec2 location = e->getLocationInView();
		location = GameManager::getWorld()->getDefaultCamera()->convertToWorldSpaceAR(location - GameManager::getVisibleSize() / 2);
		
		//Aim to mouse location
		Vec2 aimDirection = location - this->getSprite()->getPosition();
		float radian = aimDirection.getAngle(Vec2(0, 1));
		float angle = radian * 180 / M_PI;
		this->getSprite()->setRotation(angle);
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseListener, this->sprite);


	// Init keyboard event listeners
	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(Player::onKeyPressed, this);
	keyboardListener->onKeyReleased = CC_CALLBACK_2(Player::onKeyReleased, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this->sprite);
}



void Player::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {
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
	setDirection(newDirection);
}

void Player::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {
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
	setDirection(newDirection);
}

void Player::levelUp() {
	this->level++;
	if (this->level == 2) {
		GunLV2* gunLV2 = new GunLV2();
		gunLV2->getSprite()->setPosition(Vec2(sprite->getContentSize().width / 2, 0));
		this->sprite->addChild(gunLV2->getSprite());
		this->guns.push_back(gunLV2);
	}
}


void Player::onConnect(network::SIOClient* client) {
	// SocketIO::connect success
	log("SocketIO connect sucess!");
	_client->emit("message", "User001 connect success");
}
void Player::onMessage(network::SIOClient* client, const std::string& data) {
	// SocketIO::send receive
	log("On Message: data from socket server: %s", data.c_str());
	_client->emit("message", "User001 reply message");
}
void Player::onClose(network::SIOClient* client) {
	// SocketIO::disconnect success
	log("On Close: socket disconnect success");
}
void Player::onError(network::SIOClient* client, const std::string& data) {
	// SocketIO::failed
	log("On Error: socket failed!");
}

void Player::onReceiveEvent(network::SIOClient* client, const std::string& data) {
	log("On Receive Event: data from socket server: %s", data.c_str());
};
