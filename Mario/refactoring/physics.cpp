#include "physics.hpp"

void physics::ApplyGravity(types::Object* obj) {
	obj->IsFly = true;
	obj->verticalSpeed += GRAVITY;
}

void physics::MoveObjectVertical(GameContext::Context* ctx, types::Object* obj) {
	physics::ApplyGravity(obj);
	objects::SetPosition(obj, obj->x, obj->y + obj->verticalSpeed);
	for(int i = 0; i < ctx->brickCount; i++) {
		if(collision::IsCollision(*obj, ctx->brick[i])) {
			if(obj->verticalSpeed > 0) {
				obj->IsFly = false;
			}

			if((ctx->brick[i].type == BLOCK_QUESTION) && obj->verticalSpeed < 0 && obj->type == PLAYER_TYPE) {
				ctx->brick[i].type = BLOCK_DASH;
				types::Object* newCoin = objects::GetNewCoin(&ctx->coinCount, &ctx->coin);
				objects::InitObj(newCoin,
					ctx->brick[i].x,
					ctx->brick[i].y-3,
					COIN_TYPE,
					3, 2,
					COIN_SPEED);
				newCoin->verticalSpeed -= COIN_JUMP_FORCE;
			}

			obj->y -= obj->verticalSpeed;
			obj->verticalSpeed = 0;

			if(ctx->brick[i].type == BLOCK_DOOR && obj->type == PLAYER_TYPE) {
				ctx->level++;
				if(ctx->level > MAX_LEVEL) ctx->level = 1;
				collision::PlayerDead(ctx);
			}
			break;
		}
	}
}

void physics::MoveObjectHorizontal(GameContext::Context* ctx, types::Object* obj) {
	obj->x += obj->horizontalSpeed;

	for(int i = 0; i < ctx->brickCount; i++) {
		if(collision::IsCollision(*obj, ctx->brick[i])) {
			obj->x -= obj->horizontalSpeed;
			obj->horizontalSpeed = -obj->horizontalSpeed;
			return;
		}
	}

	if(obj->type == ENEMY_TYPE) {
		types::Object tmp = *obj;
		physics::MoveObjectVertical(ctx, &tmp);
		if(tmp.IsFly) {
			obj->x -= obj->horizontalSpeed;
			obj->horizontalSpeed = -obj->horizontalSpeed;
		}
	}
}
