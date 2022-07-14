#include "GameManager.h"
#include <cstdlib>
#include <ctime>
//#include <math.h>
#include "Avenger.h"
#include "Raptor.h"

USING_NS_CC;

Scene* GameManager::world = NULL;
std::vector<Entity*> GameManager::enemies;
std::vector<Entity*> GameManager::entities;

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
	const float padding = -100;
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
	for (Entity* enemy : enemies) {
		if (enemy != NULL) {
			enemy->update(dt);
		}
	}
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

	(*_entity) = NULL;
	(*_enemy) = NULL;
}