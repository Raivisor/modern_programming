#include "collision.hpp"
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

void collision::PlayerDead(const int level,
			   int* score,
			   types::Object** brick,
			   int* brickCount,
			   types::Object** enemy,
			   int* enemyCount,
			   types::Object** coin,
			   int* coinCount,
			   types::Object* mario) {
	napms(100);
	level::CreateLevel(level, score,
			   brick, brickCount, 
			   enemy, enemyCount,
			   coin, coinCount,
			   mario);
}

void collision::MarioCollision(const int level,
		    int* score,
		    types::Object** brick,
		    int* brickCount,
		    types::Object** enemy,
		    int* enemyCount,
		    types::Object** coin,
		    int* coinCount,
		    types::Object* mario) {
	for(int i = 0; i < (*enemyCount); i++) {
		if(collision::IsCollision((*mario), (*enemy)[i])) {
			if((*mario).IsFly &&
			   (*mario).verticalSpeed > 0 &&
			   (*mario).y + (*mario).height < (*enemy)[i].y + (*enemy)[i].height*0.5) {
				collision::DeleteEnemy(enemyCount, enemy, i);
				(*score) += ENEMY_SCORE;
				i--;
				continue;	
			} else { 
				PlayerDead(level, score,
					   brick, brickCount,
					   enemy, enemyCount,
					   coin, coinCount,
					   mario);
			}
		}
	}
	for(int i = 0; i < (*coinCount); i++) {
		if(IsCollision((*mario), (*coin)[i])) {
			collision::DeleteCoin(coinCount, coin, i);
			(*score) += COIN_SCORE;
			i--;
			continue;	
		}
	}	
}
