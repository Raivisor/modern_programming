#include "level.hpp"

#include <cstdlib>

void level::LoadBrick(const types::Brick* levelBrick,
		      const int count,
		      types::Object** brick,
		      int* brickCount) {
	for(int i = 0; i < count; i++) {
		objects::InitObj(objects::GetNewBrick(brickCount, brick),
				 levelBrick[i].x,
				 levelBrick[i].y,
				 levelBrick[i].type,
				 levelBrick[i].width,
				 levelBrick[i].height);
	}
}

void level::LoadEnemy(const types::Enemy* enemies, 
		      const int count,
		      types::Object** enemy,
		      int* enemyCount) {
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

void level::CreateLevel(const int level,
		 int* score,
		 types::Object** brick,
		 int* brickCount,
		 types::Object** enemy,
		 int* enemyCount,
		 types::Object** coin,
		 int* coinCount,
		 types::Object* mario) {
	(*brickCount) = 0;
	(*brick) = (types::Object*)realloc((*brick), 0);
	(*enemyCount) = 0;
	(*enemy) = (types::Object*)realloc((*enemy), 0);
	(*coinCount) = 0;
	(*coin) = (types::Object*)realloc((*coin), 0);

	objects::InitObj(&mario, 39, 10, PLAYER_TYPE, 3, 3, ABS_SPEED);
	(*score) = 0;

	if(level == 1) {
		level::LoadBrick(data::level1Brick,
			  sizeof(data::level1Brick)/sizeof(data::level1Brick[0]),
			  brick,
			  brickCount);
	} else if(level == 2) {
		level::LoadBrick(data::level2Brick,
				 sizeof(data::level2Brick)/sizeof(data::level2Brick[0]),
				 brick,
				 brickCount);
		level::LoadEnemy(data::level2Enemies, 
				   sizeof(data::level2Enemies)/sizeof(data::level2Enemies[0]),
				   enemy,
				   enemyCount);
	} else if(level == 3) {
		level::LoadBrick(data::level3Brick,
				 sizeof(data::level3Brick)/sizeof(data::level3Brick[0]),
				 brick,
				 brickCount);
		level::LoadEnemy(data::level3Enemies, 
				   sizeof(data::level3Enemies)/sizeof(data::level3Enemies[0]),
				   enemy,
				   enemyCount);

	}
}
