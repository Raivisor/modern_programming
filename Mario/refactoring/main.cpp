#include "collision.hpp"
#include "constants.hpp"
#include "gameContext.hpp"
#include "level.hpp"
#include "map.hpp"
#include "physics.hpp"
#include "types.hpp"

#include <ncurses.h>
#include <cstdlib>

void InitNcurses() {
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, true);
	curs_set(0);
	nodelay(stdscr, true);
}

int main() {
	InitNcurses();
	GameContext::Context ctx;
	
	level::CreateLevel(&ctx);

	int ch;
	float speed = 0;
	do {
		ch = getch();

		if(ch == KEY_A && speed < ABS_SPEED) ctx.speed += ABS_SPEED;
		if(ch == KEY_D && speed > -ABS_SPEED) ctx.speed -= ABS_SPEED;
		if(ch == SPACE && !ctx.mario.IsFly) ctx.mario.verticalSpeed -= JUMP_FORCE;

		map::MoveMapHorizontal(&ctx);
		physics::MoveObjectVertical(&ctx, &ctx.mario);
		collision::MarioCollision(&ctx);
		
		if(ctx.mario.y > MAP_HEIGHT) { 
			collision::PlayerDead(&ctx);
		}
			
		map::RenderMap(&ctx);
		
		napms(16);
	} while(ch != ESC);

	free(ctx.brick);
	free(ctx.enemy);
	free(ctx.coin);
	endwin();
	return 0;
}
