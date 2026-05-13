#pragma once

#include "collisions.hpp"
#include "constants.hpp"
#include "objects.hpp"
#include "types.hpp"
#include "physics.hpp"

namespace map {
	void ClearMap(char map[MAP_HEIGHT][MAP_WIDTH+1]);
	
	void ShowMap(char map[MAP_HEIGHT][MAP_WIDTH+1]);

	void PutScoreOnMap(char map[MAP_HEIGHT][MAP_WIDTH+1], const int score);

	bool IsOnMap(const int x, const int y);

	void PutObjectOnMap(char map[MAP_HEIGHT][MAP_WIDTH], types::Object* obj);

	void MoveMapHorizontal(const float dx,
			       types::Object* mario,
			       types::Object** brick, const int* brickCount,
			       types::Object** enemy, const int* enemyCount,
			       types::Object** coin, const int* coinCount);

	void RenderMap(char map[MAP_HEIGHT][MAP_WIDTH+1],
		       int* level, int* score,
		       const types::Object** brick, const int* brickCount,
		       const types::Object** enemy, const int* enemyCount,
		       const types::Object** coin, const int* coinCount,
		       const types::Object* mario);
}
