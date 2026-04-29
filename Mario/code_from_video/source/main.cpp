#include <cstdio>
#include <math.h>
#include <ncurses.h>
#include <cstring>

#define MAP_WIDTH 195
#define MAP_HEIGHT 50
#define ABS_SPEED 0.5
#define VERTICAL_SPEED 1
#define KEY_A 97
#define KEY_D 100
#define ESC 27
#define SPACE 32

struct Object {
	float x, y;
	float width, height;
	float vertSpeed;
	bool IsFly;
};

char map[MAP_HEIGHT][MAP_WIDTH+1];
Object mario;
Object *brick = nullptr;
int brickLength;

void ClearMap() {
	for(int i = 0; i < MAP_WIDTH; i++){
		map[0][i] = '.';
	}
	map[0][MAP_WIDTH] = '\0';
	for(int i = 1; i < MAP_HEIGHT; i++){
		strcpy(map[i], map[0]);
	}
}

void ShowMap() {
	clear();

	for(int i = 0; i < MAP_HEIGHT; i++) {
		printw("%s\n", map[i]);
	}

	refresh();
}

bool IsOnMap(int x, int y) {
	return ((x >= 0) && (x < MAP_WIDTH) && (y >= 0) && (y < MAP_HEIGHT));
}

void SetPosition(Object* obj, float xPos, float yPos) {
	obj->x = xPos;
	obj->y = yPos;
}

void InitObj(Object* obj, float xPos, float yPos, float width = 1, float height = 1){
	SetPosition(obj, xPos, yPos);
	obj->width = width;
	obj->height = height;
	obj->vertSpeed = 0;
}

void PutObjectOnMap(Object* obj) {
	int ix = round(obj->x);
	int iy = round(obj->y);
	int iWidth = round(obj->width);
	int iHeight = round(obj->height);
	for(int i = ix; i < (ix + iWidth); i++) {
		for(int j = iy; j < (iy + iHeight); j++) {
			if(IsOnMap(i, j)) map[j][i] = '@';
		}
	}
}

bool IsCollision(Object obj1, Object obj2) {
	return(((obj1.x + obj1.width) > obj2.x) &&
		(obj1.x < (obj2.x + obj2.width)) &&
		((obj1.y + obj1.height) > obj2.y) &&
		(obj1.y < (obj2.y + obj2.height)));
}

void MoveObjectVertical(Object* obj) {
	obj->IsFly = true;
	obj->vertSpeed += 0.05;
	SetPosition(obj, obj->x, obj->y + obj->vertSpeed);
	for(int i = 0; i < brickLength; i++) {
		if(IsCollision(*obj, brick[i])) {
			obj->IsFly = false;
			obj->y -= obj->vertSpeed;
			obj->vertSpeed = 0;
			break;
		}
	}
}

void MoveMapHorizontal(float dx) {
	mario.x -= dx;
	for(int i = 0; i < brickLength; i++) {
		if(IsCollision(mario, brick[i])) {
			mario.x += dx;
			return;
		}
	}
	mario.x += dx;
	for(int i = 0; i < brickLength; i++) {
		brick[i].x += dx;
	}
}

void CreateLevel() {
	InitObj(&mario, 39, 10, 3, 3);
	brickLength = 5;
	brick = (Object*)malloc( sizeof(*brick) * brickLength);
	InitObj(brick+0, 20, 20, 40, 5);
	InitObj(brick+1, 60, 15, 10, 10);
	InitObj(brick+2, 80, 20, 20, 5);
	InitObj(brick+3, 120, 15, 10, 10);
	InitObj(brick+4, 150, 20, 40, 5);
}

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
	
	CreateLevel();

	int ch;
	float speed = 0;
	do {
		ch = getch();

		ClearMap();

		PutObjectOnMap(&mario);
		for(int i = 0; i < brickLength; i++) {
			PutObjectOnMap(&brick[i]);
		}

		if(ch == KEY_A && speed < ABS_SPEED) speed += ABS_SPEED;
		if(ch == KEY_D && speed > -ABS_SPEED) speed -= ABS_SPEED;
		if(ch == SPACE && !mario.IsFly) mario.vertSpeed -= VERTICAL_SPEED;

		MoveMapHorizontal(speed);

		MoveObjectVertical(&mario);
		
		ShowMap();
		
		napms(13);
	} while(ch != ESC);

	endwin();
	free(brick);
	return 0;
}
