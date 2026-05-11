#include "objects.hpp"

#include <cstdlib>

void objects::SetPosition(types::Object* obj, const float xPos, float yPos) {
	obj->x = xPos;
	obj->y = yPos;
}

void objects::InitObj(types::Object* obj,
		     const float xPos,
		     const float yPos,
		     const char type,
		     const float width,
		     const float height,
		     const float speed
	) {
	objects::SetPosition(obj, xPos, yPos);
	obj->width = width;
	obj->height = height;
	obj->verticalSpeed = 0;
	obj->type = type;
	obj->horizontalSpeed = speed;
}

types::Object* objects::GetNewBrick(int* brickCount, types::Object** brick) {
	(*brickCount)++;
	(*brick) = (types::Object*)realloc((*brick), sizeof(types::Object) * (*brickCount));
	return (*brick) + (*brickCount) - 1;
}

types::Object* objects::GetNewEnemy(int* enemyCount, types::Object** enemy) {
	(*enemyCount)++;
	(*enemy) = (types::Object*)realloc((*enemy), sizeof(types::Object) * (*enemyCount));
	return (*enemy) + (*enemyCount) - 1;
}

types::Object* objects::GetNewCoin(int* coinCount, types::Object** coin) {
	(*coinCount)++;
	(*coin) = (types::Object*)realloc((*coin), sizeof(types::Object) * (*coinCount));
	return (*coin) + (*coinCount) - 1;
}
