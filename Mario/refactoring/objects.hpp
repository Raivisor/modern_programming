#pragma once

#include "types.hpp"

namespace objects {
	void SetPosition(types::Object* obj, const float xPos, const float yPos);

	void InitObj(types::Object* obj,
		     const float xPos,
		     const float yPos,
		     const char type,
		     const float width = 1,
		     const float height = 1,
		     const float speed = 0);

	types::Object* GetNewBrick(int* brickCount, types::Object** brick);

	types::Object* GetNewEnemy(int* enemyCount, types::Object** enemy);

	types::Object* GetNewCoin(int* coinCount, types::Object** coin);
}
