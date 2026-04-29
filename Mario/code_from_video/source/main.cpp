#include <cstdio>
#include <math.h>
#include <ncurses.h>
#include <cstring>

#define mapWidth 195
#define mapHeight 50

struct Object {
	float x, y;
	float width, height;
	float vertSpeed;
	bool IsFly;
};

char map[mapHeight][mapWidth+1];
Object mario;
Object brick[1];

void ClearMap() {
	for(int i = 0; i < mapWidth; i++){
		map[0][i] = '.';
	}
	map[0][mapWidth] = '\0';
	for(int i = 1; i < mapHeight; i++){
		strcpy(map[i], map[0]);
	}
}

void ShowMap() {
	clear();

	for(int i = 0; i < mapHeight; i++) {
		printw("%s\n", map[i]);
	}

	refresh();
}

bool IsOnMap(int x, int y) {
	return ((x >= 0) && (x < mapWidth) && (y >= 0) && (y < mapHeight));
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
	if(IsCollision(*obj, brick[0])) {
		obj->IsFly = false;
		obj->y -= obj->vertSpeed;
		obj->vertSpeed = 0;
	}
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
	
	InitObj(&mario, 10, 20, 3, 3);
	InitObj(brick, 5, 30, 40, 5);
	
	char ch;
	do {
		ch = getch();

		ClearMap();

		PutObjectOnMap(&mario);
		PutObjectOnMap(&brick[0]);
		
		if((!mario.IsFly) && ch == 32) mario.vertSpeed -= 1;

		MoveObjectVertical(&mario);
		
		ShowMap();
		
		timeout(15);
	} while(ch != 27);

	endwin();
	return 0;
}
