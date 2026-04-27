#include <cstdio>
#include <math.h>

#define mapWidth 86
#define mapHeight 45

struct Object {
	float x, y;
	float width, height;
};

char map[mapHeight][mapWidth+1];
Object mario;

void ClearMap() {
	for(int i = 0; i < mapWidth; i++){
		map[0][i] = '.';
	}
	map[0][mapWidth] = '\0';
	for(int i = 1; i < mapHeight; i++){
		sprintf(map[i], map[0]);
	}
}

void ShowMap() {
	map[mapHeight-1][mapWidth-1] = '\0';
	for(int i = 0; i < mapHeight; i++) {
		printf("%s", map[i]);
	}
}

void SetPosition(Object* obj, float xPos, float yPos) {
	obj->x = xPos;
	obj->y = yPos;
}

void InitObj(Object* obj, float xPos, float yPos, float width = 1, float height = 1){
	SetPosition(obj, xPos, yPos);
	obj->width = width;
	obj->height = height;
}

void PutObjectOnMap(Object* obj) {
	int ix = round(obj->x);
	int iy = round(obj->y);
	int iWidth = round(obj->width);
	int iHeight = round(obj->height);
	for(int i = ix; i < (ix + iWidth); i++) {
		for(int j = iy; j < (iy + iHeight); j++) {
			map[j][i] = '@';
		}
	}
}

int main() {
	InitObj(&mario, 10, 20, 3, 3);
	ClearMap();
	PutObjectOnMap(&mario);
	ShowMap();
	return 0;
}
