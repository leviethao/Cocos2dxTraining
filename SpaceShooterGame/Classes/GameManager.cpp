#include "GameManager.h"
#include <cstdlib>
#include <ctime>
//#include <math.h>
#include "Avenger.h"
#include "Raptor.h"
#include "ClosingScene.h"

USING_NS_CC;

Scene* GameManager::world = NULL;
std::vector<Entity*> GameManager::enemies;
std::vector<Entity*> GameManager::entities;
bool GameManager::isPause = false;

Player* GameManager::player;

GameManager::GameManager() {
}

GameManager::~GameManager() {

}

void GameManager::setWorld(Scene* world) {
	GameManager::world = world;
}

Scene* GameManager::getWorld() {
	return GameManager::world;
}

Size GameManager::getVisibleSize() {
	return Director::getInstance()->getVisibleSize();
}

Vec2 GameManager::getVisibleOrigin() {
	return Director::getInstance()->getVisibleOrigin();
}

void GameManager::setPlayer(Player* player) {
	GameManager::player = player;
}

Player* GameManager::getPlayer() {
	return player;
}

void GameManager::start() {
	srand(time(NULL));

	// Schedule spawn enemies
	world->schedule([](float dt) {
		spawnEnemies();
	}, 1, "SpawnEnemies");
}

void GameManager::spawnEnemies() {
	int enemyMaxRand = 1;
	int enemyMinRand = 0;
	int enemyType = rand() % (enemyMaxRand - enemyMinRand + 1) + enemyMinRand;

	int positionMaxRand = 100;
	int positionMinRand = -100;
	int positionX = rand() % (positionMaxRand - positionMinRand + 1) + positionMinRand;
	int positionY = rand() % (positionMaxRand - positionMinRand + 1) + positionMinRand;

	Vec2 direction = Vec2(positionX, positionY);
	direction.normalize();
	const float padding = 100;
	Vec2 position = direction * (getVisibleSize().width / 2 + padding) + getVisibleSize() / 2;

	Entity* enemy = NULL;
	switch (enemyType) {
	case Entity::Avenger:
		enemy = new Avenger();
		break;
	case Entity::Raptor:
		enemy = new Raptor();
		break;
	default:
		enemy = new Avenger();
		break;
	}

	enemy->getSprite()->setPosition(position);
	GameManager::world->addChild(enemy->getSprite());
	enemy->init();
	enemies.push_back(enemy);
	entities.push_back(enemy);
}

void GameManager::update(float dt) {
	if (isPause) {
		pauseGame();
		return;
	}
	player->update(dt);
	for (Entity* enemy : enemies) {
		if (enemy != NULL) {
			enemy->update(dt);
		}
	}
}

void GameManager::addEntity(Entity* entity) {
	world->addChild(entity->getSprite());
	entities.push_back(entity);
}

Entity* GameManager::findEntity(Sprite* sprite) {
	for (Entity* entity : entities) {
		if (entity != NULL) {
			if (entity->getSprite() == sprite) return entity;
		}
	}

	return NULL;
}

void GameManager::destroyEntity(Entity* entity) {
	auto _entity = std::find(entities.begin(), entities.end(), entity);
	auto _enemy = std::find(enemies.begin(), enemies.end(), entity);

	/*std::remove(entities.begin(), entities.end(), entity);
	std::remove(enemies.begin(), enemies.end(), entity);*/
	entity->destroy();
	delete entity;

	if (_entity != entities.end()) (*_entity) = NULL;
	if (_enemy != enemies.end()) (*_enemy) = NULL;
}

void GameManager::pauseGame() {
	// Pause player
	player->pause();

	// Pause entities
	for (Entity* entity : entities) {
		if (entity != NULL) {
			entity->pause();
		}
	}

	// Pause game world
	//world->pause();
}

void GameManager::resumeGame() {
	// Resume Player
	player->resume();

	// Resume entities
	for (Entity* entity : entities) {
		if (entity != NULL) {
			entity->resume();
		}
	}

	//world->resume();
}

void GameManager::end() {
	auto closingScene = ClosingScene::create();
	Director::getInstance()->replaceScene(closingScene);
}

void GameManager::pause() {
	isPause = true;
}

void GameManager::resume() {
	isPause = false;
	resumeGame();
}

