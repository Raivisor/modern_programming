#pragma once

#include "constants.hpp"
#include "data.hpp"
#include "gameContext.hpp"
#include "objects.hpp"
#include "types.hpp"

namespace level {
	void LoadBrick(const types::Brick* levelBrick, const int count, 
		       types::Object** brick, int* brickCount);

	void LoadEnemy(const types::Enemy* levelEnemies, const int count,
		       types::Object** enemy, int* enemyCount);

	void CreateLevel(GameContext::Context* ctx);
}
