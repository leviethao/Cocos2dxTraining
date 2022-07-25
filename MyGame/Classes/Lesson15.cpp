
#include "ui/CocosGUI.h"
#include "Lesson15.h"

USING_NS_CC;

Scene* Lesson15::createScene()
{
    return Lesson15::create();
}

// on "init" you need to initialize your instance
bool Lesson15::init()
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
    mouseListener->onMouseDown = CC_CALLBACK_1(Lesson15::onMouseDown, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);


	// Database
	this->db = NULL;

    // connect to server
    _client = network::SocketIO::connect("http://127.0.0.1:3000", *this);
    _client->on("message", CC_CALLBACK_2(Lesson15::onReceiveEvent, this));

    //this->scheduleUpdate();
    return true;
}


//void Lesson15::update(float dt) {
//    // Handle update game state here
//}

void Lesson15::onMouseDown(Event* event) {
    EventMouse* e = (EventMouse*)event;
    Vec2 location = e->getLocationInView();

    Vec2 direction = location - this->mySprite->getPosition();
    direction.normalize();

	this->createTable("myDatabase", "Master", "(id TEXT PRIMARY KEY, name TEXT, age INT)");
	this->insertData("myDatabase", "Master", "id, name, age", "'User002', 'Adam', 19");
	this->insertData("myDatabase", "Master", "id, name, age", "'User003', 'Eva', 17");
	this->selectData("myDatabase", "Master", "*", "");

    _client->emit("SayHello", "Hello from client");
}

bool Lesson15::connectDB(const std::string& dbName) {
	this->db = NULL;
	bool isSuccess = false;
	std::string dbPath = FileUtils::getInstance()->getWritablePath() + dbName + ".db";
	int result = sqlite3_open(dbPath.c_str(), &db);
	if (result == SQLITE_OK) {
		log("Open database successful, dbPath: %s", dbPath.c_str());
		isSuccess = true;
	}
	else {
		log("Open database failed");
		isSuccess = false;
	}

	return isSuccess;
}

bool Lesson15::createTable(const std::string& dbName, const std::string& tableName, const std::string& columnDefinition) {
	int result = 0;
	bool isSuccess = false;
	char* err;

	// Connect database
	if (this->connectDB(dbName) == false) return false;

	std::string sql = "CREATE TABLE " + tableName + " " + columnDefinition + ";";
	result = sqlite3_exec(db, sql.c_str(), NULL, NULL, &err);
	if (result == SQLITE_OK) {
		log("Create table successfuly");
		isSuccess = true;
	}
	else {
		log("Create table failed: %s", err);
		isSuccess = false;
	}

	// Close connection
	sqlite3_close(db);
	
	return isSuccess;
}

bool Lesson15::insertData(const std::string& dbName, const std::string& tableName, const std::string& columns, const std::string& values) {
	// Connect database
	if (this->connectDB(dbName) == false) return false;
	std::string sql = "INSERT INTO " + tableName + " (" + columns + ") VALUES (" + values + ");";
	char* err = 0;
	bool isSuccess = false;
	int result = sqlite3_exec(db, sql.c_str(), NULL, NULL, &err);
	if (result == SQLITE_OK) {
		log("Insert success");
		isSuccess = true;
	}
	else {
		log("Insert failed: %s", err);
		isSuccess = false;
	}

	// Close connection
	sqlite3_close(db);

	return isSuccess;
}

void Lesson15::updateData() {

}

int callback(void* data, int argc, char** argv, char** azColName) {
	// Logging row values
	for (int i = 0; i < argc; i++) {
		log("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}

	// Logging converted type values
	log("%s -> %s", azColName[0], (std::string(argv[0]) + "_something").c_str());
	log("%s -> %s", azColName[1], (std::string(argv[1]) + "_something").c_str());
	log("%s -> %d", azColName[2], std::atoi(argv[2]) + 100);
	log("%s -> %.2f", azColName[2], std::atof(argv[2]) + 100);
	return 0;
};

void Lesson15::selectData(const std::string& dbName, const std::string& tableName, const std::string& columns, const std::string& condition) {
	// Connect database
	if (this->connectDB(dbName) == false) return;
	
	std::string sql = "SELECT " + columns + " FROM " + tableName + (condition != "" ? (" WHERE " + condition) : ""); +";";
	int result = 0;
	char* zErrMsg = 0;
	result = sqlite3_exec(db, sql.c_str(), callback, NULL, &zErrMsg);

	if (result != SQLITE_OK) {
		log("SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	else {
		log("Operation done successfully\n");
	}

	// Close connection
	sqlite3_close(db);
}

void Lesson15::deleteData() {

}




void Lesson15::onConnect(cocos2d::network::SIOClient* client) {
    // SocketIO::connect success
    log("SocketIO connect sucess!");
    _client->emit("message", "User001 connect success");
}
void Lesson15::onMessage(cocos2d::network::SIOClient* client, const std::string& data) {
    // SocketIO::send receive
    log("On Message: data from socket server: %s", data.c_str());
    //_client->emit("message", "User001 reply message");
}
void Lesson15::onClose(cocos2d::network::SIOClient* client) {
    // SocketIO::disconnect success
    log("On Close: socket disconnect success");
}
void Lesson15::onError(cocos2d::network::SIOClient* client, const std::string& data) {
    // SocketIO::failed
    log("On Error: socket failed!");
}

void Lesson15::onReceiveEvent(cocos2d::network::SIOClient* client, const std::string& data) {
    //log("On Receive Event: data from socket server: %s", data.c_str());
};
