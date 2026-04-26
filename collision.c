#include "collision.h"
#include "globals.h"

int CheckCollision(float x1, float y1, float w1, float h1,
                   float x2, float y2, float w2, float h2) {
    return !(x1 + w1 <= x2 || x2 + w2 <= x1 ||
             y1 + h1 <= y2 || y2 + h2 <= y1);
}

int IsWall(int x, int y) {
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) return 1;
    return map[y][x] == '#' || tileMap[y][x].type == TILE_WALL;
}

int IsHazard(int x, int y) {
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) return 0;
    return tileMap[y][x].type == TILE_LAVA;
}
