#pragma once

#include "collision.hpp"
#include "constants.hpp"
#include "gameContext.hpp"
#include "objects.hpp"
#include "types.hpp"
#include "physics.hpp"

namespace map {
	void ClearMap(char map[MAP_HEIGHT][MAP_WIDTH+1]);
	
	void ShowMap(char map[MAP_HEIGHT][MAP_WIDTH+1]);

	void PutScoreOnMap(char map[MAP_HEIGHT][MAP_WIDTH+1], const int score);

	bool IsOnMap(const int x, const int y);

	void PutObjectOnMap(char map[MAP_HEIGHT][MAP_WIDTH+1], types::Object* obj);

	void MoveMapHorizontal(GameContext::Context* ctx);

	void RenderMap(GameContext::Context* ctx);
}
