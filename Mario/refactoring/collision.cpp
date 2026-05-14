#include "collision.hpp"

#include <cstdlib>
#include <ncurses.h>

void collision::DeleteEnemy(int* enemyCount, types::Object** enemy, int i) {
	(*enemyCount)--;
	(*enemy)[i] = (*enemy)[*enemyCount];
	(*enemy) = (types::Object*)realloc((*enemy), sizeof(types::Object) * (*enemyCount));
}

void collision::DeleteCoin(int* coinCount, types::Object** coin, int i) {
	(*coinCount)--;
	(*coin)[i] = (*coin)[*coinCount];
	(*coin) = (types::Object*)realloc((*coin), sizeof(types::Object) * (*coinCount));
}

bool collision::IsCollision(const types::Object& obj1, const types::Object& obj2) {
	return(((obj1.x + obj1.width) > obj2.x) &&
		(obj1.x < (obj2.x + obj2.width)) &&
		((obj1.y + obj1.height) > obj2.y) &&
		(obj1.y < (obj2.y + obj2.height)));
}

void collision::PlayerDead(GameContext::Context* ctx) {
	napms(100);
	level::CreateLevel(ctx);
}

void collision::MarioCollision(GameContext::Context* ctx) {
	for(int i = 0; i < ctx->enemyCount; i++) {
		if(collision::IsCollision(ctx->mario, ctx->enemy[i])) {
			if(ctx->mario.IsFly &&
			   ctx->mario.verticalSpeed > 0 &&
			   ctx->mario.y + ctx->mario.height < ctx->enemy[i].y + ctx->enemy[i].height*0.5) {
				collision::DeleteEnemy(&ctx->enemyCount, &ctx->enemy, i);
				ctx->score += ENEMY_SCORE;
				i--;
				continue;	
			} else { 
				PlayerDead(ctx);
			}
		}
	}
	for(int i = 0; i < ctx->coinCount; i++) {
		if(IsCollision(ctx->mario, ctx->coin[i])) {
			collision::DeleteCoin(&ctx->coinCount, &ctx->coin, i);
			ctx->score += COIN_SCORE;
			i--;
			continue;	
		}
	}	
}
