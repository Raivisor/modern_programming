#include <math.h>
#include <ncurses.h>
#include <cstring>


char map[MAP_HEIGHT][MAP_WIDTH+1];
Object mario;

Object *brick = nullptr;
int brickCount;

Object *enemy = nullptr;
int enemyCount;

Object *coin = nullptr;
int coinCount;

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

void LoadBrick(Brick *bricks, int count){
	for(int i = 0; i < count; i++) {
		InitObj(GetNewBrick(), 
				bricks[i].x, 
				bricks[i].y,
				bricks[i].type,
				bricks[i].width, 
				bricks[i].height);
	}
}

void LoadEnemies(Enemy *enemies, int count) {
    for(int i = 0; i < count; i++) {
        InitObj(GetNewEnemy(), 
                enemies[i].x, 
                enemies[i].y, 
                enemies[i].type, 
                enemies[i].width, 
                enemies[i].height, 
                enemies[i].speed);
    }
}

void CreateLevel(int level) {
	brickCount = 0;
	brick = (Object*)realloc(brick, 0);
	enemyCount = 0;
	enemy = (Object*)realloc(enemy, 0);
	coinCount = 0;
	coin = (Object*)realloc(coin, 0);

	InitObj(&mario, 39, 10, PLAYER_TYPE, 3, 3, ABS_SPEED);
	score = 0;

	if(level == 1) {
		LoadBrick(level1Brick, sizeof(level1Brick)/sizeof(level1Brick[0]));
	} else if(level == 2) {
		LoadBrick(level2Brick, sizeof(level2Brick)/sizeof(level2Brick[0]));
		LoadEnemies(level2Enemies, sizeof(level2Enemies)/sizeof(level2Enemies[0]));
	}
	else if(level == 3) {
		LoadBrick(level3Brick, sizeof(level3Brick)/sizeof(level3Brick[0]));
		LoadEnemies(level3Enemies, sizeof(level3Enemies)/sizeof(level3Enemies[0]));
	}
}

void PutObjectOnMap(Object* obj) {
	int x = round(obj->x);
	int y = round(obj->y);
	int width = round(obj->width);
	int height = round(obj->height);
	for(int i = x; i < (x + width); i++) {
		for(int j = y; j < (y + height); j++) {
			if(IsOnMap(i, j)) map[j][i] = obj->type;
		}
	}
}

void DeleteEnemy(int i) {
	enemyCount--;
	enemy[i] = enemy[enemyCount];
	enemy = (Object*)realloc(enemy, sizeof(Object) * enemyCount);
}

void DeleteCoin(int i) {
	coinCount--;
	coin[i] = coin[coinCount];
	coin = (Object*)realloc(coin, sizeof(Object) * coinCount);
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

			if((brick[i].type == BLOCK_QUESTION) && obj->verticalSpeed < 0 && obj == &mario) {
				brick[i].type = BLOCK_DASH;
				InitObj(GetNewCoin(), brick[i].x, brick[i].y-3, COIN_TYPE, 3, 2, COIN_SPEED);
				coin[coinCount - 1].verticalSpeed -= COIN_JUMP_FORCE;
			}

			obj->y -= obj->verticalSpeed;
			obj->verticalSpeed = 0;
			if(brick[i].type == BLOCK_DOOR) {
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

	if(obj->type == ENEMY_TYPE) {
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
	for(int i = 0; i < enemyCount; i++) {
		enemy[i].x += dx;
	}
	for(int i = 0; i < coinCount; i++) {
		coin[i].x += dx;
	}
}

void MarioCollision() {
	for(int i = 0; i < enemyCount; i++) {
		if(IsCollision(mario, enemy[i])) {
			if(mario.IsFly &&
			   mario.verticalSpeed > 0 &&
			   mario.y + mario.height < enemy[i].y + enemy[i].height*0.5) {
				DeleteEnemy(i);
				mario.verticalSpeed = JUMP_FORCE_ON_KILL;
				MoveObjectVertical(&mario);
				score += ENEMY_SCORE;
				i--;
				continue;	
			} else { 
				PlayerDead();
			}
		}
	}
	for(int i = 0; i < coinCount; i++) {
		if(IsCollision(mario, coin[i])) {
			DeleteCoin(i);
			score += COIN_SCORE;
			i--;
			continue;	
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
	for(int i = 0; i < enemyCount; i++) {
		PutObjectOnMap(&enemy[i]);
		MoveObjectVertical(&enemy[i]);
		MoveObjectHorizontal(&enemy[i]);
	}
	for(int i = 0; i < coinCount; i++) {
		PutObjectOnMap(&coin[i]);
		MoveObjectVertical(&coin[i]);
		MoveObjectHorizontal(&coin[i]);
		if(coin[i].y > MAP_HEIGHT) {
			DeleteCoin(i);
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
	free(enemy);
	free(coin);
	return 0;
}
