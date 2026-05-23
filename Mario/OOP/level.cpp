#include "level.hpp"

#include "config.hpp"
#include <cstdlib>

namespace {
    struct BrickData {
        float x, y, w, h;
        EntityType type;
    };

    struct EnemyData {
        float x, y, w, h;
        EntityType type;
        float speed;
    };

    const BrickData level1Bricks[] = {
        {20, 20, 40, 5, EntityType::BLOCK_WALL},
        {100, 20, 20, 5, EntityType::BLOCK_WALL},
        {120, 15, 10, 10, EntityType::BLOCK_WALL},
        {150, 20, 40, 5, EntityType::BLOCK_WALL},
        {60, 15, 40, 10, EntityType::BLOCK_WALL},

        {30, 10, 5, 3, EntityType::BLOCK_QUESTION},
        {50, 10, 5, 3, EntityType::BLOCK_QUESTION},
        {60, 5, 10, 3, EntityType::BLOCK_DASH},
        {70, 5, 5, 3, EntityType::BLOCK_QUESTION},
        {75, 5, 5, 3, EntityType::BLOCK_DASH},
        {80, 5, 5, 3, EntityType::BLOCK_QUESTION},
        {85, 5, 10, 3, EntityType::BLOCK_DASH},

        {210, 15, 10, 10, EntityType::BLOCK_DOOR}
    };
    const int level1BrickCount = sizeof(level1Bricks) / sizeof(level1Bricks[0]);

    const BrickData level2Bricks[] = {
        {20, 20, 40, 5, EntityType::BLOCK_WALL},
        {60, 15, 10, 10, EntityType::BLOCK_WALL},
        {80, 20, 20, 5, EntityType::BLOCK_WALL},
        {120, 15, 10, 10, EntityType::BLOCK_WALL},
        {150, 20, 40, 5, EntityType::BLOCK_WALL},
        {210, 15, 10, 10, EntityType::BLOCK_DOOR}
    };
    const int level2BrickCount = sizeof(level2Bricks) / sizeof(level2Bricks[0]);

    const BrickData level3Bricks[] = {
        {20, 20, 40, 5, EntityType::BLOCK_WALL},
        {80, 20, 15, 5, EntityType::BLOCK_WALL},
        {120, 15, 15, 10, EntityType::BLOCK_WALL},
        {160, 10, 15, 15, EntityType::BLOCK_DOOR}
    };
    const int level3BrickCount = sizeof(level3Bricks) / sizeof(level3Bricks[0]);

    const EnemyData level2Enemies[] = {
        {25, 10, 3, 2, EntityType::ENEMY, 0.3335f},
        {80, 10, 3, 2, EntityType::ENEMY, 0.3335f},
        {65, 10, 3, 2, EntityType::ENEMY, 0.3335f},
        {120, 10, 3, 2, EntityType::ENEMY, 0.3335f},
        {160, 10, 3, 2, EntityType::ENEMY, 0.3335f},
        {175, 10, 3, 2, EntityType::ENEMY, 0.3335f}
    };
    const int level2EnemyCount = sizeof(level2Enemies) / sizeof(level2Enemies[0]);

    const EnemyData level3Enemies[] = {
        {25, 10, 3, 2, EntityType::ENEMY, 0.3335f},
        {50, 10, 3, 2, EntityType::ENEMY, 0.3335f},
        {80, 10, 3, 2, EntityType::ENEMY, 0.3335f},
        {90, 10, 3, 2, EntityType::ENEMY, 0.3335f},
        {120, 10, 3, 2, EntityType::ENEMY, 0.3335f},
        {130, 10, 3, 2, EntityType::ENEMY, 0.3335f}
    };
    const int level3EnemyCount = sizeof(level3Enemies) / sizeof(level3Enemies[0]);
}

using namespace sea;

Level::Level(int level)
    : bricks(nullptr), brickCount(0), enemies(nullptr), enemyCount(0), coins(nullptr), coinCount(0)
{
    loadLevel(level);
}

Level::~Level() {
    delete[] bricks;
    delete[] enemies;
    delete[] coins;
}

Level::Level(Level&& other) noexcept
    : bricks(other.bricks), brickCount(other.brickCount),
      enemies(other.enemies), enemyCount(other.enemyCount),
      coins(other.coins), coinCount(other.coinCount)
{
    other.bricks = nullptr;
    other.brickCount = 0;
    other.enemies = nullptr;
    other.enemyCount = 0;
    other.coins = nullptr;
    other.coinCount = 0;
}

Level& Level::operator=(Level&& other) noexcept {
    if (this != &other) {
        delete[] bricks;
        delete[] enemies;
        delete[] coins;

        bricks = other.bricks;
        brickCount = other.brickCount;
        enemies = other.enemies;
        enemyCount = other.enemyCount;
        coins = other.coins;
        coinCount = other.coinCount;

        other.bricks = nullptr;
        other.brickCount = 0;
        other.enemies = nullptr;
        other.enemyCount = 0;
        other.coins = nullptr;
        other.coinCount = 0;
    }
    return *this;
}

void Level::setEnemies(Enemy* newEnemies, int count) {
	delete[] enemies;
	enemies = newEnemies;
	enemyCount = count;
}

void Level::setCoins(Coin* newCoins, int count) {
	delete[] coins;
	coins = newCoins;
	coinCount = count;
}

void Level::addCoin(const Coin& coin) {
	Coin* newCoins = new Coin[coinCount + 1];
	for (int i = 0; i < coinCount; ++i) {
		newCoins[i] = coins[i];
	}
	newCoins[coinCount] = coin;
	delete[] coins;
	coins = newCoins;
	++coinCount;
}

void Level::loadLevel(int level) {
    delete[] bricks;
    delete[] enemies;
    delete[] coins;
    bricks = nullptr;
    enemies = nullptr;
    coins = nullptr;

    switch(level) {
	case 1:
		brickCount = level1BrickCount;
		bricks = new Brick[brickCount];
		for (int i = 0; i < brickCount; ++i) {
		    bricks[i] = Brick(level1Bricks[i].x, level1Bricks[i].y,
				      level1Bricks[i].w, level1Bricks[i].h,
				      level1Bricks[i].type);
		}
		enemyCount = 0;
		enemies = nullptr;
		coinCount = 0;
		coins = nullptr;
		break;
	case 2:
		brickCount = level2BrickCount;
		bricks = new Brick[brickCount];
		for (int i = 0; i < brickCount; ++i) {
		    bricks[i] = Brick(level2Bricks[i].x, level2Bricks[i].y,
				      level2Bricks[i].w, level2Bricks[i].h,
				      level2Bricks[i].type);
		}
		enemyCount = level2EnemyCount;
		enemies = new Enemy[enemyCount];
		for (int i = 0; i < enemyCount; ++i) {
		    enemies[i] = Enemy(level2Enemies[i].x, level2Enemies[i].y,
				       level2Enemies[i].w, level2Enemies[i].h,
				       level2Enemies[i].type,
				       level2Enemies[i].speed, 0);
		}
		coinCount = 0;
		coins = nullptr;
		break;
	case 3:
		brickCount = level3BrickCount;
		bricks = new Brick[brickCount];
		for (int i = 0; i < brickCount; ++i) {
		    bricks[i] = Brick(level3Bricks[i].x, level3Bricks[i].y,
				      level3Bricks[i].w, level3Bricks[i].h,
				      level3Bricks[i].type);
		}
		enemyCount = level3EnemyCount;
		enemies = new Enemy[enemyCount];
		for (int i = 0; i < enemyCount; ++i) {
		    enemies[i] = Enemy(level3Enemies[i].x, level3Enemies[i].y,
				       level3Enemies[i].w, level3Enemies[i].h,
				       level3Enemies[i].type,
				       level3Enemies[i].speed, 0);
		}
		coinCount = 0;
		coins = nullptr;
		break;
	default:
		brickCount = 0;
		bricks = nullptr;
		enemyCount = 0;
		enemies = nullptr;
		coinCount = 0;
		coins = nullptr;
		break;
    }
}
