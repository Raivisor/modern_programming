#pragma once

#include "types.hpp"
#include "constants.hpp"
#include "objects.hpp"
#include "collision.hpp"

namespace physics {
	void ApplyGravity(types::Object* obj);

	void MoveObjectVertical(int* level,
				int* score,
				types::Object* obj,
				types::Object** brick,
				int* brickCount,
				types::Object** enemy,
				int* enemyCount,
				types::Object** coin,
				int* coinCount,
				types::Object* mario);

	void MoveObjectHorizontal(int* level,
				  int* score,
				  types::Object* obj, 
				  types::Object** brick, 
				  int* brickCount,
				  types::Object** enemy,
				  int* enemyCount,
				  types::Object** coin,
				  int* coinCount,
				  types::Object* mario);
}
