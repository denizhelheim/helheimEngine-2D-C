#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#define widht 16
#define height 16

int playerX = 1;
int playerY = 1;

char map[widht][height]; // GAME MAP

void DrawMap() {
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

void UpdateMap() {
    DrawMap();
}

void MovePlayer() {
    char input = getch();

    switch (input) {
        case 'w':
            playerY--;
            UpdateMap();
            break;
        case 's':
            playerY++;
            UpdateMap();
            break;
        case 'a':
            playerX--;
            UpdateMap();
            break;
        case 'd':
            playerX++;
            UpdateMap();
            break;
    }
}

int main() {
    DrawMap();


    while (1) {
        MovePlayer();
    }






    return 0;
}