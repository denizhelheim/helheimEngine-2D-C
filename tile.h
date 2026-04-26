#ifndef TILE_H
#define TILE_H

#include "types.h"

void InitializeTileMap();
void SetTile(int x, int y, TileType type);
void ClearMap(char mapToClean[HEIGHT][WIDTH]);
void InitializeDefaultMap();

#endif // TILE_H
