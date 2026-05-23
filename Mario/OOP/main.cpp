#include "game.hpp"
#include <ncurses.h>

int main() {
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, true);
	curs_set(0);
	nodelay(stdscr, true);

	sea::Game game;
	game.run();

	endwin();
	return 0;
}
