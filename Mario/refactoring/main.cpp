#include <cstdio>
#include <math.h>
#include <ncurses.h>
#include <cstring>

#define MAP_WIDTH 195
#define MAP_HEIGHT 50
#define ABS_SPEED 1
#define JUMP_FORCE 1
#define JUMP_FORCE_ON_KILL -0.5
#define GRAVITY 0.05
#define COIN_JUMP_FORCE -0.7
#define KEY_A 97
#define KEY_D 100
#define ESC 27
#define SPACE 32
#define MAX_LEVEL 3
#define COIN_SCORE 100
#define ENEMY_SCORE 50

struct Object {
	float x, y;
	float width, height;
	float verticalSpeed;
	float horizontalSpeed;
	bool IsFly;
	char type;
};

char map[MAP_HEIGHT][MAP_WIDTH+1];
Object mario;

Object *brick = nullptr;
int brickCount;

Object *moving = nullptr;
int movingCount;

int level = 1;
int score; 

void InitNcurses() {
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, true);
	curs_set(0);
	nodelay(stdscr, true);
}

void ClearMap() {
	for(int i = 0; i < MAP_WIDTH; i++){
		map[0][i] = ' ';
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

void PutScoreOnMap() {
	char c[30];
	sprintf(c, "Score: %d", score);
	int len = strlen(c);
	for(int i = 0; i < len; i++) {
		map[1][i+5] = c[i];
	}

}

bool IsOnMap(int x, int y) {
	return ((x >= 0) && (x < MAP_WIDTH) && (y >= 0) && (y < MAP_HEIGHT));
}

void SetPosition(Object* obj, float xPos, float yPos) {
	obj->x = xPos;
	obj->y = yPos;
}

void InitObj(Object* obj, float xPos, float yPos, char type, float width = 1, float height = 1){
	SetPosition(obj, xPos, yPos);
	obj->width = width;
	obj->height = height;
	obj->verticalSpeed = 0;
	obj->type = type;
	obj->horizontalSpeed = 0.2;
}

Object* GetNewBrick() {
	brickCount++;
	brick = (Object*)realloc(brick, sizeof(Object) * brickCount);
	return brick + brickCount - 1;
}

Object* GetNewMoving() {
	movingCount++;
	moving = (Object*)realloc(moving, sizeof(Object) * movingCount);
	return moving + movingCount - 1;
}

void CreateLevel(int level) {
	brickCount = 0;
	brick = (Object*)realloc(brick, 0);
	movingCount = 0;
	moving = (Object*)realloc(moving, 0);

	InitObj(&mario, 39, 10, '@', 3, 3);
	score = 0;

	if(level == 1) {
		InitObj(GetNewBrick(), 20, 20, '#',  40, 5);
			InitObj(GetNewBrick(), 30, 10, '?',  5, 3);
			InitObj(GetNewBrick(), 50, 10, '?',  5, 3);
		InitObj(GetNewBrick(), 60, 15, '#',  40, 10);
			InitObj(GetNewBrick(), 60, 5, '-',  10, 3);
			InitObj(GetNewBrick(), 70, 5, '?',  5, 3);
			InitObj(GetNewBrick(), 75, 5, '-',  5, 3);
			InitObj(GetNewBrick(), 80, 5, '?',  5, 3);
			InitObj(GetNewBrick(), 85, 5, '-',  10, 3);
		InitObj(GetNewBrick(), 100, 20, '#', 20, 5);
		InitObj(GetNewBrick(), 120, 15, '#', 10, 10);
		InitObj(GetNewBrick(), 150, 20, '#', 40, 5);
		InitObj(GetNewBrick(), 210, 15, '+', 10, 10);
	} else if(level == 2) {
		InitObj(GetNewBrick(), 20, 20, '#',  40, 5);
		InitObj(GetNewBrick(), 60, 15, '#',  10, 10);
		InitObj(GetNewBrick(), 80, 20, '#', 20, 5);
		InitObj(GetNewBrick(), 120, 15, '#', 10, 10);
		InitObj(GetNewBrick(), 150, 20, '#', 40, 5);
		InitObj(GetNewBrick(), 210, 15, '+', 10, 10);
		
		InitObj(GetNewMoving(), 25, 10, 'o', 3, 2);
		InitObj(GetNewMoving(), 80, 10, 'o', 3, 2);
		InitObj(GetNewMoving(), 65, 10, 'o', 3, 2);
		InitObj(GetNewMoving(), 120, 10, 'o', 3, 2);
		InitObj(GetNewMoving(), 160, 10, 'o', 3, 2);
		InitObj(GetNewMoving(), 175, 10, 'o', 3, 2);
	}
	else if(level == 3) {
		InitObj(GetNewBrick(), 20, 20, '#',  40, 5);
		InitObj(GetNewBrick(), 80, 20, '#',  15, 5);
		InitObj(GetNewBrick(), 120, 15, '#', 15, 10);
		InitObj(GetNewBrick(), 160, 10, '+', 15, 15);
		
		InitObj(GetNewMoving(), 25, 10, 'o', 3, 2);
		InitObj(GetNewMoving(), 50, 10, 'o', 3, 2);
		InitObj(GetNewMoving(), 80, 10, 'o', 3, 2);
		InitObj(GetNewMoving(), 90, 10, 'o', 3, 2);
		InitObj(GetNewMoving(), 120, 10, 'o', 3, 2);
		InitObj(GetNewMoving(), 130, 10, 'o', 3, 2);
	}
}

void PutObjectOnMap(Object* obj) {
	int x = round(obj->x);
	int y = round(obj->y);
	int Width = round(obj->width);
	int Height = round(obj->height);
	for(int i = x; i < (x + Width); i++) {
		for(int j = y; j < (y + Height); j++) {
			if(IsOnMap(i, j)) map[j][i] = obj->type;
		}
	}
}

void DeleteMoving(int i) {
	movingCount--;
	moving[i] = moving[movingCount];
	moving = (Object*)realloc(moving, sizeof(Object) * movingCount);
}

void PlayerDead() {
	napms(100);
	CreateLevel(level);
}

bool IsCollision(Object obj1, Object obj2) {
	return(((obj1.x + obj1.width) > obj2.x) &&
		(obj1.x < (obj2.x + obj2.width)) &&
		((obj1.y + obj1.height) > obj2.y) &&
		(obj1.y < (obj2.y + obj2.height)));
}

void ApplyGravity(Object* obj) {
	obj->IsFly = true;
	obj->verticalSpeed += GRAVITY;
}

void MoveObjectVertical(Object* obj) {
	ApplyGravity(obj);
	SetPosition(obj, obj->x, obj->y + obj->verticalSpeed);
	for(int i = 0; i < brickCount; i++) {
		if(IsCollision(*obj, brick[i])) {
			if(obj->verticalSpeed > 0) {
				obj->IsFly = false;
			}

			if((brick[i].type == '?') && obj->verticalSpeed < 0 && obj == &mario) {
				brick[i].type = '-';
				InitObj(GetNewMoving(), brick[i].x, brick[i].y-3, '$', 3, 2);
				moving[movingCount - 1].verticalSpeed -= COIN_JUMP_FORCE;
			}

			obj->y -= obj->verticalSpeed;
			obj->verticalSpeed = 0;
			if(brick[i].type == '+') {
				level++;
				if(level > MAX_LEVEL) level = 1;
				PlayerDead();
			}
			break;
		}
	}
}

void MoveObjectHorizontal(Object* obj) {
	obj->x += obj->horizontalSpeed;

	for(int i = 0; i < brickCount; i++) {
		if(IsCollision(*obj, brick[i])) {
			obj->x -= obj->horizontalSpeed;
			obj->horizontalSpeed = -obj->horizontalSpeed;
			return;
		}
	}

	if(obj->type == 'o') {
		Object tmp = *obj;
		MoveObjectVertical(&tmp);
		if(tmp.IsFly) {
			obj->x -= obj->horizontalSpeed;
			obj->horizontalSpeed = -obj->horizontalSpeed;
		}
	}
}

void MoveMapHorizontal(float dx) {
	mario.x -= dx;
	for(int i = 0; i < brickCount; i++) {
		if(IsCollision(mario, brick[i])) {
			mario.x += dx;
			return;
		}
	}
	mario.x += dx;
	for(int i = 0; i < brickCount; i++) {
		brick[i].x += dx;
	}
	for(int i = 0; i < movingCount; i++) {
		moving[i].x += dx;
	}
}

void MarioCollision() {
	for(int i = 0; i < movingCount; i++) {
		if(IsCollision(mario, moving[i])) {
			if(moving[i].type == 'o'){
				if(mario.IsFly &&
				   mario.verticalSpeed > 0 &&
				   mario.y + mario.height < moving[i].y + moving[i].height*0.5) {
					DeleteMoving(i);
					mario.verticalSpeed = JUMP_FORCE_ON_KILL*JUMP_FORCE;
					MoveObjectVertical(&mario);
					score += ENEMY_SCORE;
					i--;
					continue;	
				} else { 
					PlayerDead();
				}
			} else if(moving[i].type == '$') {
				DeleteMoving(i);
				score += COIN_SCORE;
				i--;
				continue;
			}
		}
	}
}

void RenderMap() {
	ClearMap();
	PutScoreOnMap();
	PutObjectOnMap(&mario);
	for(int i = 0; i < brickCount; i++) {
		PutObjectOnMap(&brick[i]);
	}
	for(int i = 0; i < movingCount; i++) {
		PutObjectOnMap(&moving[i]);
		MoveObjectVertical(&moving[i]);
		MoveObjectHorizontal(&moving[i]);
		if(moving[i].y > MAP_HEIGHT) {
			DeleteMoving(i);
			i--;
			continue;
		}
	}
	ShowMap();
}

int main() {
	InitNcurses();
	
	CreateLevel(level);

	int ch;
	float speed = 0;
	do {
		ch = getch();

		if(ch == KEY_A && speed < ABS_SPEED) speed += ABS_SPEED;
		if(ch == KEY_D && speed > -ABS_SPEED) speed -= ABS_SPEED;
		if(ch == SPACE && !mario.IsFly) mario.verticalSpeed -= JUMP_FORCE;

		MoveMapHorizontal(speed);
		MoveObjectVertical(&mario);
		MarioCollision();
		
		if(mario.y > MAP_HEIGHT) PlayerDead();
			
		RenderMap();
		
		napms(13);
	} while(ch != ESC);

	endwin();
	free(brick);
	free(moving);
	return 0;
}
