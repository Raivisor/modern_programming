#include "data.hpp"
#include "constants.hpp"
#include "types.hpp"

const types::Brick data::level1Brick[] = {
	{20, 20,  40, 5, BLOCK_WALL},
	{100, 20, 20, 5, BLOCK_WALL},
	{120, 15, 10, 10, BLOCK_WALL},
	{150, 20, 40, 5, BLOCK_WALL},
	{60, 15,  40, 10, BLOCK_WALL},

	{30, 10,  5, 3, BLOCK_QUESTION},
	{50, 10,  5, 3, BLOCK_QUESTION},
	{60, 5,  10, 3, BLOCK_DASH},
	{70, 5,  5, 3, BLOCK_QUESTION},
	{75, 5,  5, 3, BLOCK_DASH},
	{80, 5,  5, 3, BLOCK_QUESTION},
	{85, 5,  10, 3, BLOCK_DASH},

	{210, 15, 10, 10, BLOCK_DOOR}
};

const types::Brick data::level2Brick[] = {
	{20, 20,  40, 5, BLOCK_WALL},
	{60, 15,  10, 10, BLOCK_WALL},
	{80, 20, 20, 5, BLOCK_WALL},
	{120, 15, 10, 10, BLOCK_WALL},
	{150, 20, 40, 5, BLOCK_WALL},
	{210, 15, 10, 10, BLOCK_DOOR},
};

const types::Brick data::level3Brick[] = {
	{20, 20,  40, 5, BLOCK_WALL},
	{80, 20,  15, 5, BLOCK_WALL},
	{120, 15, 15, 10, BLOCK_WALL},
	{160, 10, 15, 15, BLOCK_DOOR},
};

const types::Enemy data::level2Enemies[] = {
	{25, 10, 3, 2, ENEMY_TYPE, ENEMY_SPEED},
	{80, 10, 3, 2, ENEMY_TYPE, ENEMY_SPEED},
	{65, 10, 3, 2, ENEMY_TYPE, ENEMY_SPEED},
	{120, 10, 3, 2, ENEMY_TYPE, ENEMY_SPEED},
	{160, 10, 3, 2, ENEMY_TYPE, ENEMY_SPEED},
	{175, 10, 3, 2, ENEMY_TYPE, ENEMY_SPEED}
};

const types::Enemy data::level3Enemies[] = {
	{25, 10, 3, 2, ENEMY_TYPE, ENEMY_SPEED},
	{50, 10, 3, 2, ENEMY_TYPE, ENEMY_SPEED},
	{80, 10, 3, 2, ENEMY_TYPE, ENEMY_SPEED},
	{90, 10, 3, 2, ENEMY_TYPE, ENEMY_SPEED},
	{120, 10, 3, 2, ENEMY_TYPE, ENEMY_SPEED},
	{130, 10, 3, 2, ENEMY_TYPE, ENEMY_SPEED}
};
