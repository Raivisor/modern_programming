#pragma once

#include "data.hpp"
#include "constants.hpp"
#include "types.hpp"
#include "objects.hpp"

namespace level {
	void LoadBrick(const types::Brick* levelBrick, 
		       const int count, 
		       types::Object** brick,
		       int* brickCount);

	void LoadEnemy(const types::Enemy* levelEnemies, 
		       const int count,
		       types::Object** enemy,
		       int* enemyCount);

	void CreateLevel(const int level,
			 int* score,
			 types::Object** brick,
			 int* brickCount,
			 types::Object** enemy,
			 int* enemyCount,
			 types::Object** coin,
			 int* coinCount,
			 types::Object* mario);
}
