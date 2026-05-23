#pragma once

#include "brick.hpp"
#include "enemy.hpp"
#include "coin.hpp"

namespace sea {
	class Level {
		private:
			Brick* bricks;
			int brickCount;

			Enemy* enemies;
			int enemyCount;
			
			Coin* coins;
			int coinCount;
		public:
			Level(int level);
			~Level();

			Level(const Level&) = delete;
			Level& operator=(const Level& other) = delete;

			Level(Level&& other) noexcept;
			Level& operator=(Level&& other) noexcept;

			Brick* getBricks() { return bricks; }
			int getBrickCount() const { return brickCount; }

			Enemy* getEnemies() { return enemies; }
			int getEnemyCount() const { return enemyCount; }

			Coin* getCoins() { return coins; }
			int getCoinCount() const {return coinCount; }

			void setEnemies(sea::Enemy* newEnemies, int count);
			void setCoins(sea::Coin* newCoins, int count);

			void addCoin(const Coin& coin);

			void loadLevel(int level);
	};
}
