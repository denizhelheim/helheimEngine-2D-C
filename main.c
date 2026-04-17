#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define widht 16 // GAME MAP WIDTH
#define height 16 // GAME MAP HEIGHT

int playerX = 1; // PLAYER STARTING X POSITION
int playerY = 1; // PLAYER STARTING Y POSITION

char map[height][widht]; // GAME MAP ARRAY

void InitializeMap() { // FUNCTION TO INITIALIZE THE MAP
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < widht; x++) {
            map[y][x] = '.';
        }
    }
    // PLACE WALLS ON MAP -- YOU CAN CHANGE THESE POSITIONS TO CREATE DIFFERENT WALLS
    map[5][5] = '#';
    map[7][7] = '#';
    map[3][8] = '#';
    map[10][3] = '#';
    map[12][12] = '#';
}

void DrawMap() { // FUNCTION TO DRAW THE GAME MAP
    system("cls");

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < widht; x++) {
            if (x == playerX && y == playerY) {
                printf("P");
            } else {
                printf("%c", map[y][x]);
            }
        }
        printf("\n");
    }
}

void UpdateMap() { // FUNCTION TO UPDATE THE GAME MAP
    DrawMap();
}

int IsWall(int x, int y) { // FUNCTION TO CHECK IF POSITION IS A WALL
    return (map[y][x] == '#');
}

void MovePlayer() { // FUNCTION TO MOVE THE PLAYER
    char input = getch();

    switch (input) {
        case 'w':
            if (playerY > 0 && !IsWall(playerX, playerY - 1)) {
                playerY--;
                UpdateMap();
            }
            break;
        case 's':
            if (playerY < height - 1 && !IsWall(playerX, playerY + 1)) {
                playerY++;
                UpdateMap();
            }
            break;
        case 'a':
            if (playerX > 0 && !IsWall(playerX - 1, playerY)) {
                playerX--;
                UpdateMap();
            }
            break;
        case 'd':
            if (playerX < widht - 1 && !IsWall(playerX + 1, playerY)) {
                playerX++;
                UpdateMap();
            }
            break;
    }
}

int main() { // MAIN FUNCTION
    InitializeMap();
    DrawMap();
    while (1) {
        MovePlayer();
    }

    return 0;
}