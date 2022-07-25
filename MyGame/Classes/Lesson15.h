#ifndef __LESSON15_H__
#define __LESSON15_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

#include "SQLite/sqlite3.h"

#include "network/SocketIO.h"

using namespace std;

class Lesson15 : public cocos2d::Scene, public cocos2d::network::SocketIO::SIODelegate
{
private:
    sqlite3* db;
    cocos2d::network::SIOClient* _client;
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    //void update(float dt);
    void onMouseDown(cocos2d::Event* event);

    cocos2d::Sprite* mySprite;


    // ========= SQLite =========

    /**
    * dbName: "myDatabase"
    */
    bool connectDB(const std::string& dbName);

    /**
    * dbName: "myDatabase"
    * tableName: "Master"
    * columnDefinition: "(id TEXT PRIMARY KEY, value INT)"
    * return: isSuccess boolean
    */
    bool createTable(const std::string& dbName, const std::string& tableName, const std::string& columnDefinition);

    /**
    * dbName: "myDatabase"
    * tableName: "Master"
    * columns: "id, name, age"
    * values: "'User001', 'John', 18"
    * return: isSuccess boolean
    */
    bool insertData(const std::string& dbName, const std::string& tableName, const std::string& columns, const std::string& values);
    
    void updateData();

    /**
    * dbName: "myDatabase"
    * tableName: "Master"
    * columns: "id, name, age"
    * condition: "id='User001' AND age=18 LIMIT 1"
    */
    void selectData(const std::string& dbName, const std::string& tableName, const std::string& columns, const std::string& condition);
    void deleteData();

    // socket.io even\vent listener
    void onReceiveEvent(cocos2d::network::SIOClient* client, const std::string& data);
    // SIODelegate
    virtual void onConnect(cocos2d::network::SIOClient* client);
    virtual void onMessage(cocos2d::network::SIOClient* client, const std::string& data);
    virtual void onClose(cocos2d::network::SIOClient* client);
    virtual void onError(cocos2d::network::SIOClient* client, const std::string& data);

    // implement the "static create()" method manually
    CREATE_FUNC(Lesson15);
    
};

#endif // __LESSON15_H__
