#pragma once

#include "types.hpp"
#include "level.hpp"

namespace collision {
	void DeleteEnemy(int* enemyCount, types::Object** ememy, int i);

	void DeleteCoin(int* coinCount, types::Object** coin, int i);

	bool IsCollision(const types::Object& obj1, const types::Object& obj2);
	
	void PlayerDead(const int level,
			int* score,
			types::Object** brick,
			int* brickCount,
			types::Object** enemy,
			int* enemyCount,
			types::Object** coin,
			int* coinCount,
			types::Object* mario);

	void MarioCollision(const int level,
			    int* score,
			    types::Object** brick,
			    int*brickCount,
			    types::Object** enemy,
			    int* enemyCount,
			    types::Object** coin,
			    int* coinCount
			    types::Object* mario
			    );
}
