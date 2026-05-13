#include "physics.hpp"

void physics::ApplyGravity(types::Object* obj) {
	obj->IsFly = true;
	obj->verticalSpeed += GRAVITY;
}

void physics::MoveObjectVertical(int* level,
				 int* score,
				 types::Object* obj,
				 types::Object** brick,
				 int* brickCount,
				 types::Object** enemy,
				 int* enemyCount,
				 types::Object** coin,
				 int* coinCount,
				 types::Object* mario) {
	physics::ApplyGravity(obj);
	objects::SetPosition(obj, obj->x, obj->y + obj->verticalSpeed);
	for(int i = 0; i < (*brickCount); i++) {
		if(collision::IsCollision(*obj, (*brick)[i])) {
			if(obj->verticalSpeed > 0) {
				obj->IsFly = false;
			}

			if(((*brick)[i].type == BLOCK_QUESTION) && obj->verticalSpeed < 0 && obj->type == PLAYER_TYPE) {
				(*brick)[i].type = BLOCK_DASH;
				objects::InitObj(objects::GetNewCoin(coinCount, coin),
					(*brick)[i].x,
					(*brick)[i].y-3,
					COIN_TYPE,
					3,
					2,
					COIN_SPEED);
				(*coin)[(*coinCount) - 1].verticalSpeed -= COIN_JUMP_FORCE;
			}

			obj->y -= obj->verticalSpeed;
			obj->verticalSpeed = 0;
			if((*brick)[i].type == BLOCK_DOOR && obj->type == PLAYER_TYPE) {
				(*level)++;
				if((*level) > MAX_LEVEL) *level = 1;
				collision::PlayerDead(level, score,
						      brick, brickCount,
						      enemy, enemyCount,
						      coin, coinCount,
						      mario);
			}
			break;
		}
	}
}

void physics::MoveObjectHorizontal(int* level,
				   int* score,
				   types::Object* obj, 
				   types::Object** brick, 
				   int* brickCount,
				   types::Object** enemy,
				   int* enemyCount,
				   types::Object** coin,
				   int* coinCount,
				   types::Object* mario) {
	obj->x += obj->horizontalSpeed;

	for(int i = 0; i < (*brickCount); i++) {
		if(collision::IsCollision(*obj, (*brick)[i])) {
			obj->x -= obj->horizontalSpeed;
			obj->horizontalSpeed = -obj->horizontalSpeed;
			return;
		}
	}

	if(obj->type == ENEMY_TYPE) {
		types::Object tmp = *obj;
		physics::MoveObjectVertical(level, score, &tmp,
				   brick, brickCount,
				   enemy, enemyCount,
				   coin, coinCount,
				   mario);
		if(tmp.IsFly) {
			obj->x -= obj->horizontalSpeed;
			obj->horizontalSpeed = -obj->horizontalSpeed;
		}
	}
}
