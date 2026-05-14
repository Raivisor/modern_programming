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
	sprintf(c, "Score: %d", score);
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

void map::MoveMapHorizontal(GameContext::Context* ctx) {
	ctx->mario.x -= ctx->speed;
	for(int i = 0; i < ctx->brickCount; i++) {
		if(collision::IsCollision(ctx->mario, ctx->brick[i])) {
			ctx->mario.x += ctx->speed;
			return;
		}
	}
	ctx->mario.x += ctx->speed;
	for(int i = 0; i < ctx->brickCount; i++) ctx->brick[i].x += ctx->speed;
	for(int i = 0; i < ctx->enemyCount; i++) ctx->enemy[i].x += ctx->speed;
	for(int i = 0; i < ctx->coinCount; i++) ctx->coin[i].x += ctx->speed;
}

void map::RenderMap(GameContext::Context* ctx) {
	map::ClearMap(ctx->map);
	map::PutScoreOnMap(ctx->map, ctx->score);
	map::PutObjectOnMap(ctx->map, &ctx->mario);

	for(int i = 0; i < ctx->brickCount; i++) {
		map::PutObjectOnMap(ctx->map, ctx->brick + i);
	}
	
	for(int i = 0; i < ctx->enemyCount; i++) {
		physics::MoveObjectVertical(ctx, &ctx->enemy[i]);
		physics::MoveObjectHorizontal(ctx, &ctx->enemy[i]);
		map::PutObjectOnMap(ctx->map, ctx->enemy + i);
	}
	for(int i = 0; i < ctx->coinCount; i++) {
		physics::MoveObjectVertical(ctx, &ctx->coin[i]);
		physics::MoveObjectHorizontal(ctx, &ctx->coin[i]);
		if(ctx->coin[i].y > MAP_HEIGHT) {
			collision::DeleteCoin(&ctx->coinCount, &ctx->coin, i);
			i--;
			continue;
		}
		map::PutObjectOnMap(ctx->map, ctx->coin + i);
	}
	map::ShowMap(ctx->map);
}
