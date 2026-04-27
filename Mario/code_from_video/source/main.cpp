#include <cstdio>

#define mapWidth 86
#define mapHeight 45

struct Coordinates {
	float x, y;
}

char map[mapHeight][mapWidth+1];

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

int main() {
	ClearMap();
	ShowMap();
	return 0;
}
