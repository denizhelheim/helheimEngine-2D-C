#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define widht 16 // GAME MAP WIDTH
#define height 16 // GAME MAP HEIGHT

int playerX = 1; // PLAYER STARTING X POSITION
int playerY = 1; // PLAYER STARTING Y POSITION

char map[widht][height]; // GAME MAP ARRAY

void DrawMap() { // FUNCTION TO DRAW THE GAME MAP
    system("cls");

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < widht; x++) {
            if (x == playerX && y == playerY) {
                printf("P");
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

void MovePlayer() { // FUNCTION TO MOVE THE PLAYER
    char input = getch();

    switch (input) {
        case 'w':
            if (playerY > 0) {
                playerY--;
                UpdateMap();
            }
            break;
        case 's':
            if (playerY < height - 1) {
                playerY++;
                UpdateMap();
            }
            break;
        case 'a':
            if (playerX > 0) {
                playerX--;
                UpdateMap();
            }
            break;
        case 'd':
            if (playerX < widht - 1) {
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