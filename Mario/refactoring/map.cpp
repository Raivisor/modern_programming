#include "map.hpp"

#include <ncurses.h>
#include <cstring>
#include <math.h>

void map::ClearMap(char map[MAP_HEIGHT][MAP_WIDTH+1]) {
	for(int i = 0; i < MAP_WIDTH; i++) {
		map[0][i] = ' ';
	}
	map[0][MAP_WIDTH] = '\0';
	for(int i = 1; i < MAP_HEIGHT; i++) {
		strcpy(map[i], map[0]);
	}
}

void map::ShowMap(char map[MAP_HEIGHT][MAP_WIDTH+1]) {
	clear();
	for(int i = 0; i < MAP_HEIGHT; i++) {
		printw("%s\n", map[i]);
	}
	refresh();
}

void map::PutScoreOnMap(char map[MAP_HEIGHT][MAP_WIDTH+1], const int score) {
	char c[30];
	sprintf(c, "Score: %d", *score);
	int len = strlen(c);
	for(int i = 0; i < len; i++) {
		map[1][i + 5] = c[i];
	}
}

bool map::IsOnMap(const int x, const int y) {
	return ((x >= 0) && (x < MAP_WIDTH) && (y >= 0) && (y < MAP_HEIGHT));
}

void map::PutObjectOnMap(char map[MAP_HEIGHT][MAP_WIDTH+1], types::Object* obj) {
	int x = round(obj->x);
	int y = round(obj->y);
	int width = round(obj->width);
	int height = round(obj->height);
	for(int i = x; i < (x + width); i++) {
		for(int j = y; j < (y + height); j++) {
			if(map::IsOnMap(i, j)) map[j][i] = obj->type;
		}
	}
}

void map::MoveMapHorizontal(const float dx,
			    types::Object* mario,
			    types::Object** brick, const int* brickCount,
			    types::Object** enemy, const int* enemyCount,
			    types::Object** coin, const int* coinCount) {
	mario->x -= dx;
	for(int i = 0; i < *brickCount; i++) {
		if(collision::IsCollision(*mario, (*brick)[i])) {
			mario->x += dx;
			return;
		}
	}
	mario->x += dx;
	for(int i = 0; i < *brickCount; i++) (*brick)[i].x += dx;
	for(int i = 0; i < *enemyCount; i++) (*enemy)[i].x += dx;
	for(int i = 0; i < *coinCount; i++) (*coin)[i].x += dx;
}

void map::RenderMap(char map[MAP_HEIGHT][MAP_WIDTH+1],
	       int* level, int* score,
	       const types::Object** brick, const int* brickCount, 
	       const types::Object** enemy, const int* enemyCount,
	       const types::Object** coin, const int* coinCount,
	       const types::Object* mario) {
	map::ClearMap(map);
	map::PutScoreOnMap(map, *score);
	map::PutObjectOnMap(map, mario);

	for(int i = 0; i < *brickCount; i++) {
		map::PutObjectOnMap(map, (*brick) + i);
	}
	
	for(int i = 0; i < *enemyCount; i++) {
		physics::MoveObjectVertical(level, score,
					    (*enemy) + i,
					    brick, brickCount,
					    enemy, enemyCount,
					    coin, coinCount,
					    mario);
		physics::MoveObjectHorizontal(level,
					      score,
					      (*enemy) + i,
					      brick, brickCount,
					      enemy, enemyCount,
					      coin, coinCount,
					      mario);
		map::PutObjectOnMap((*enemy) + i);
	}
	for(int i = 0; i < *coinCount; i++) {
		physics::MoveObjectVertical(level, score,
					    (*coin) + i,
					    brick, brickCount,
					    enemy, enemyCount,
					    coin, coinCount,
					    mario);
		physics::MoveObjectHorizontal(level, score,
					      (*coin) + i,
					      brick, brickCount,
					      enemy, enemyCount,
					      coin, coinCount,
					      mario);
		if((*coin)[i].y > MAP_HEIGHT) {
			collision::DeleteCoin(coinCount, coin, i);
			i--;
			continue;
		}
		map::PutObjectOnMap((*coin) + i);
	}
	map::ShowMap(map);
}
