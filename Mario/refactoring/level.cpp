#include "level.hpp"

#include <cstdlib>

void level::LoadBrick(const types::Brick* levelBrick, const int count,
		      types::Object** brick, int* brickCount) {
	for(int i = 0; i < count; i++) {
		objects::InitObj(objects::GetNewBrick(brickCount, brick),
				 levelBrick[i].x,
				 levelBrick[i].y,
				 levelBrick[i].type,
				 levelBrick[i].width,
				 levelBrick[i].height);
	}
}

void level::LoadEnemy(const types::Enemy* enemies, const int count,
		      types::Object** enemy, int* enemyCount) {
	for(int i = 0; i < count; i++) {
		objects::InitObj(objects::GetNewEnemy(enemyCount, enemy),
				 enemies[i].x,
				 enemies[i].y,
				 enemies[i].type,
				 enemies[i].width,
				 enemies[i].height,
				 enemies[i].speed);
	}
}

void level::CreateLevel(GameContext::Context* ctx) {
	ctx->brickCount = 0;
	ctx->brick = (types::Object*)realloc(ctx->brick, 0);
	ctx->enemyCount = 0;
	ctx->enemy = (types::Object*)realloc(ctx->enemy, 0);
	ctx->coinCount = 0;
	ctx->coin = (types::Object*)realloc(ctx->coin, 0);

	objects::InitObj(&ctx->mario, 39, 10, PLAYER_TYPE, 3, 3, ABS_SPEED);
	ctx->score = 0;

	if(ctx->level == 1) {
		level::LoadBrick(data::level1Brick, data::level1BrickSize,
			  	 &ctx->brick, &ctx->brickCount);
	} else if(ctx->level == 2) {
		level::LoadBrick(data::level2Brick, data::level2BrickSize,	
				 &ctx->brick, &ctx->brickCount);
		level::LoadEnemy(data::level2Enemies, data::level2EnemiesSize, 
				 &ctx->enemy, &ctx->enemyCount);
	} else if(ctx->level == 3) {
		level::LoadBrick(data::level3Brick, data::level3BrickSize, 
				 &ctx->brick, &ctx->brickCount);
		level::LoadEnemy(data::level3Enemies, data::level3EnemiesSize, 
				   &ctx->enemy, &ctx->enemyCount);

	}
}
