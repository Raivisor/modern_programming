#include "game.hpp"
#include "config.hpp"
#include "collision_handler.hpp"
#include <ncurses.h>

using namespace sea;

Game::Game()
    : currentLevel(1),
      render(Config::MAP_WIDTH, Config::MAP_HEIGHT),
      mario(39, 10, 3, 3, EntityType::PLAYER, 0, 0),
      score(0),
      running(true),
      currentLevelNumber(1)
{
    loadLevel(currentLevelNumber);
}

void Game::loadLevel(int levelNumber) {
    currentLevel = Level(levelNumber);
    mario.setX(39);
    mario.setY(10);
    mario.setVX(0);
    mario.setVY(0);
    mario.setIsAlive(true);
}

void Game::shiftWorld(float dx) {
    Brick* bricks = currentLevel.getBricks();
    int brickCount = currentLevel.getBrickCount();
    for (int i = 0; i < brickCount; ++i) {
        bricks[i].setX(bricks[i].getX() + dx);
    }

    Enemy* enemies = currentLevel.getEnemies();
    int enemyCount = currentLevel.getEnemyCount();
    for (int i = 0; i < enemyCount; ++i) {
        enemies[i].setX(enemies[i].getX() + dx);
    }

    Coin* coins = currentLevel.getCoins();
    int coinCount = currentLevel.getCoinCount();
    for (int i = 0; i < coinCount; ++i) {
        coins[i].setX(coins[i].getX() + dx);
    }
}

void Game::handleInput() {
    InputManager::getInstance().readKey();
    if (InputManager::getInstance().isExit()) {
        running = false;
    }
}

void Game::update() {
    Enemy* enemies = currentLevel.getEnemies();
    int enemyCount = currentLevel.getEnemyCount();
    for (int i = 0; i < enemyCount; ++i) {
        if (enemies[i].getIsAlive()) {
            enemies[i].update(currentLevel, physics);
        }
    }

    Coin* coins = currentLevel.getCoins();
    int coinCount = currentLevel.getCoinCount();
    for (int i = 0; i < coinCount; ++i) {
        if (coins[i].getIsAlive()) {
            coins[i].update(currentLevel, physics);
        }
    }

    const float SCROLL_THRESHOLD = 20.0f;
    if (mario.getX() < SCROLL_THRESHOLD) {
        float dx = SCROLL_THRESHOLD - mario.getX();
        mario.setX(SCROLL_THRESHOLD);
        shiftWorld(dx);
    } else if (mario.getX() > Config::MAP_WIDTH - SCROLL_THRESHOLD) {
        float dx = Config::MAP_WIDTH - SCROLL_THRESHOLD - mario.getX();
        mario.setX(Config::MAP_WIDTH - SCROLL_THRESHOLD);
        shiftWorld(dx);
    }

    checkCollisions();

    if (!mario.getIsAlive()) {
        loadLevel(currentLevelNumber);
        napms(100);
        return;
    }

    //removeDeadObjects();

    mario.update(currentLevel, physics);
}

void Game::checkCollisions() {
	Enemy* enemies = currentLevel.getEnemies();
	for (int i = 0; i < currentLevel.getEnemyCount(); ++i) {
		if (enemies[i].getIsAlive() && CollisionHandler::isCollision(mario, enemies[i])) {
		    bool wasAlive = enemies[i].getIsAlive();
		    mario.onCollision(enemies[i]);
		    if (wasAlive && !enemies[i].getIsAlive()) {
			score += Config::ENEMY_SCORE;
		    }
		}
	}

	Coin* coins = currentLevel.getCoins();
	for (int i = 0; i < currentLevel.getCoinCount(); ++i) {
		if (coins[i].getIsAlive() && CollisionHandler::isCollision(mario, coins[i])) {
		    bool wasAlive = coins[i].getIsAlive();
		    mario.onCollision(coins[i]);
		    if (wasAlive && !coins[i].getIsAlive()) {
			score += Config::COIN_SCORE;
		    }
		}
	}

	Brick* bricks = currentLevel.getBricks();
	int brickCount = currentLevel.getBrickCount();
	for (int i = 0; i < brickCount; ++i) {
		if (bricks[i].getType() == EntityType::BLOCK_DOOR &&
		    CollisionHandler::isCollisionDoor(mario, bricks[i])) {
			currentLevelNumber++;
			if (currentLevelNumber > Config::MAX_LEVEL) currentLevelNumber = 1;
			loadLevel(currentLevelNumber);
			break;
		}
		if (bricks[i].getType() == EntityType::BLOCK_QUESTION 
			&& CollisionHandler::isCollisionQuestion(mario, bricks[i])) {
			bricks[i].onCollision(mario);
			float coinX = bricks[i].getX();
			float coinY = bricks[i].getY() - 3;
			Coin newCoin(coinX, coinY, 3, 2, EntityType::COIN, 0, 0);
			newCoin.setVX(Config::COIN_SPEED);
			newCoin.setVY(Config::COIN_JUMP_FORCE);
			currentLevel.addCoin(newCoin);
			break;
			}
	}
}

void Game::removeDeadObjects() {
    Enemy* enemies = currentLevel.getEnemies();
    int enemyCount = currentLevel.getEnemyCount();
    int newEnemyCount = 0;
    for (int i = 0; i < enemyCount; ++i) {
        if (enemies[i].getIsAlive()) {
            if (i != newEnemyCount) enemies[newEnemyCount] = enemies[i];
            newEnemyCount++;
        }
    }
    if (newEnemyCount != enemyCount) {
        Enemy* newEnemies = new Enemy[newEnemyCount];
        for (int i = 0; i < newEnemyCount; ++i) newEnemies[i] = enemies[i];
        delete[] enemies;
        const_cast<Level&>(currentLevel).setEnemies(newEnemies, newEnemyCount);
    }

    Coin* coins = currentLevel.getCoins();
    int coinCount = currentLevel.getCoinCount();
    int newCoinCount = 0;
    for (int i = 0; i < coinCount; ++i) {
        if (coins[i].getIsAlive()) {
            if (i != newCoinCount) coins[newCoinCount] = coins[i];
            newCoinCount++;
        }
    }
    if (newCoinCount != coinCount) {
        Coin* newCoins = new Coin[newCoinCount];
        for (int i = 0; i < newCoinCount; ++i) newCoins[i] = coins[i];
        delete[] coins;
        const_cast<Level&>(currentLevel).setCoins(newCoins, newCoinCount);
    }
}

void Game::renderFrame() {
    render.clearMap();

    Brick* bricks = currentLevel.getBricks();
    for (int i = 0; i < currentLevel.getBrickCount(); ++i) {
        render.putEntityOnMap(bricks[i]);
    }

    Enemy* enemies = currentLevel.getEnemies();
    for (int i = 0; i < currentLevel.getEnemyCount(); ++i) {
        if (enemies[i].getIsAlive()) render.putEntityOnMap(enemies[i]);
    }

    Coin* coins = currentLevel.getCoins();
    for (int i = 0; i < currentLevel.getCoinCount(); ++i) {
        if (coins[i].getIsAlive()) render.putEntityOnMap(coins[i]);
    }

    render.putEntityOnMap(mario);
    render.putScoreOnMap(score);
    render.refreshMap();
}

void Game::run() {
    while (running) {
        handleInput();
        update();
        renderFrame();
        napms(16);
    }
}
