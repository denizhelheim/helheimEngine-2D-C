#include <stdlib.h>
#include "tile.h"
#include "globals.h"

void InitializeTileMap() {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            tileMap[y][x].type = TILE_EMPTY;
            tileMap[y][x].walkable = 1;
            tileMap[y][x].displayChar = '.';
        }
    }
}

void SetTile(int x, int y, TileType type) {
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) return;
    
    tileMap[y][x].type = type;
    
    switch (type) {
        case TILE_WALL:
            tileMap[y][x].displayChar = '#';
            tileMap[y][x].walkable = 0;
            break;
        case TILE_LAVA:
            tileMap[y][x].displayChar = '~';
            tileMap[y][x].walkable = 1;
            break;
        case TILE_ICE:
            tileMap[y][x].displayChar = '=';
            tileMap[y][x].walkable = 1;
            break;
        case TILE_EXIT:
            tileMap[y][x].displayChar = 'E';
            tileMap[y][x].walkable = 1;
            break;
        case TILE_SPAWN:
            tileMap[y][x].displayChar = 'S';
            tileMap[y][x].walkable = 1;
            break;
        default:
            tileMap[y][x].displayChar = '.';
            tileMap[y][x].walkable = 1;
    }
}

void ClearMap(char mapToClean[HEIGHT][WIDTH]) {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            mapToClean[y][x] = '.';
        }
    }
}

void InitializeDefaultMap() {
    ClearMap(map);
    InitializeTileMap();
    
    // Build walls/maze
    for (int i = 0; i < 15; i++) {
        int rx = 2 + rand() % (WIDTH - 4);
        int ry = 2 + rand() % (HEIGHT - 4);
        SetTile(rx, ry, TILE_WALL);
        map[ry][rx] = '#';
    }
    
    // Create exit
    SetTile(WIDTH - 2, HEIGHT - 2, TILE_EXIT);
    map[HEIGHT - 2][WIDTH - 2] = 'E';
    
    // Spawn some collectibles
    for (int i = 0; i < 5; i++) {
        int rx = 2 + rand() % (WIDTH - 4);
        int ry = 2 + rand() % (HEIGHT - 4);
        if (map[ry][rx] == '.') {
            map[ry][rx] = '*';
            totalStars++;
        }
    }
}
