#include "render.hpp"

#include <ncurses.h>
#include <cmath>
#include <cstring>

using namespace sea;

Render::Render(int w, int h) : width(w), height(h) {
    map = new char*[height];
    for (int i = 0; i < height; ++i) {
        map[i] = new char[width + 1];
        std::memset(map[i], ' ', width);
        map[i][width] = '\0';
    }
}

Render::~Render() {
    for (int i = 0; i < height; ++i) delete[] map[i];
    delete[] map;
}

bool Render::isOnMap(int x, int y) const {
    return x >= 0 && x < width && y >= 0 && y < height;
}

void Render::clearMap() {
    for (int i = 0; i < height; ++i) {
        std::memset(map[i], ' ', width);
        map[i][width] = '\0';
    }
}

void Render::putEntityOnMap(const Entity& entity) {
    int x = static_cast<int>(std::round(entity.getX()));
    int y = static_cast<int>(std::round(entity.getY()));
    int w = static_cast<int>(std::round(entity.getWidth()));
    int h = static_cast<int>(std::round(entity.getHeight()));
    char sym = entity.getSymbol();

    for (int row = y; row < y + h; ++row) {
        for (int col = x; col < x + w; ++col) {
            if (isOnMap(col, row)) {
                map[row][col] = sym;
            }
        }
    }
}

void Render::putScoreOnMap(int score) {
    char buf[32];
    snprintf(buf, sizeof(buf), "Score: %d", score);
    int len = strlen(buf);
    for (int i = 0; i < len && i + 5 < width; ++i) {
        if (isOnMap(i + 5, 1)) {
            map[1][i + 5] = buf[i];
        }
    }
}

void Render::refreshMap() {
    clear();
    for (int i = 0; i < height; ++i) {
        printw("%s\n", map[i]);
    }
    ::refresh();
}
