#pragma once

#include "gameContext.hpp"
#include "level.hpp"
#include "types.hpp"

namespace collision {
	void DeleteEnemy(int* enemyCount, types::Object** enemy, int i);

	void DeleteCoin(int* coinCount, types::Object** coin, int i);

	bool IsCollision(const types::Object& obj1, const types::Object& obj2);
	
	void PlayerDead(GameContext::Context* ctx);

	void MarioCollision(GameContext::Context* ctx);
}
