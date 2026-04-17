#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define widht 16 // GAME MAP WIDTH
#define height 16 // GAME MAP HEIGHT

int playerX = 1; // PLAYER STARTING X POSITION
int playerY = 1; // PLAYER STARTING Y POSITION

int wallX = 5; // WALL X POSITION
int wallY = 5; // WALL Y POSITION

char map[widht][height]; // GAME MAP ARRAY

void DrawMap() { // FUNCTION TO DRAW THE GAME MAP
    system("cls");

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < widht; x++) {
            if (x == playerX && y == playerY) {
                printf("P");
            } else if (x == wallX && y == wallY) {
                printf("#");
            } else {
                printf(".");
            }
        }
        printf("\n");
    }
}

void UpdateMap() { // FUNCTION TO UPDATE THE GAME MAP
    DrawMap();
}

int IsWall(int x, int y) { // FUNCTION TO CHECK IF POSITION IS A WALL
    return (x == wallX && y == wallY);
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
    DrawMap();
    while (1) {
        MovePlayer();
    }






    return 0;
}