#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

#define WIDTH 16   // GAME MAP WIDTH
#define HEIGHT 16  // GAME MAP HEIGHT

// Current playing variables
int playerX = 1;
int playerY = 1;
int score = 0;
int won = 0;
char map[HEIGHT][WIDTH];

// Default level (built-in)
char defaultMap[HEIGHT][WIDTH];
int defaultPlayerX = 1;
int defaultPlayerY = 1;

// Custom level (created by player)
char customMap[HEIGHT][WIDTH];
int customPlayerX = 1;
int customPlayerY = 1;
int hasCustomLevel = 0;

// Editor variables (global for simplicity)
char editorMap[HEIGHT][WIDTH];
int editorPlayerX;
int editorPlayerY;

void ClearMap(char mapToClean[HEIGHT][WIDTH]) {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            mapToClean[y][x] = '.';
        }
    }
}

void InitializeDefaultMap() {
    ClearMap(defaultMap);

    // PLACE WALLS (you can change these to create different mazes)
    defaultMap[5][5] = '#';
    defaultMap[7][7] = '#';
    defaultMap[3][8] = '#';
    defaultMap[10][3] = '#';
    defaultMap[12][12] = '#';
    defaultMap[4][10] = '#';
    defaultMap[6][2] = '#';
    defaultMap[9][13] = '#';
    defaultMap[11][6] = '#';
    defaultMap[2][12] = '#';
    defaultMap[13][9] = '#';

    // COLLECTIBLE STARS (*)
    defaultMap[2][5] = '*';
    defaultMap[8][10] = '*';
    defaultMap[13][3] = '*';
    defaultMap[4][12] = '*';
    defaultMap[10][14] = '*';

    // EXIT POINT (E)
    defaultMap[14][14] = 'E';
}

void DrawMap() {
    system("cls");

    // Draw the game map
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (x == playerX && y == playerY) {
                printf("P");
            } else {
                printf("%c", map[y][x]);
            }
        }
        printf("\n");
    }

    // HUD (On-screen information panel)
    printf("\n");
    printf("================================\n");
    printf("SCORE: %d\n", score);
    printf("================================\n");
    printf("W/A/S/D = Move\n");
    printf("Collect *, reach E!\n");
    printf("Q = Quit to menu\n");
    printf("================================\n");

    if (won) {
        printf("*** CONGRATULATIONS! YOU WON THE GAME! ***\n");
        printf("Your Final Score: %d\n", score);
    }
}

void UpdateMap() {
    DrawMap();
}

int IsWall(int x, int y) {
    return (map[y][x] == '#');
}

int MovePlayer() {
    char input = getch();

    int newX = playerX;
    int newY = playerY;

    switch (input) {
        case 'w':
        case 'W':
            newY--;
            break;
        case 's':
        case 'S':
            newY++;
            break;
        case 'a':
        case 'A':
            newX--;
            break;
        case 'd':
        case 'D':
            newX++;
            break;
        case 'q':
        case 'Q':
            system("cls");
            printf("Game closed.\nFinal Score: %d\n", score);
            printf("Press any key to return to main menu...\n");
            getch();
            return 1;  // Signal to quit to menu
    }

    // Check if the move is valid
    if (newX >= 0 && newX < WIDTH && newY >= 0 && newY < HEIGHT && !IsWall(newX, newY)) {
        char target = map[newY][newX];

        // Move the player
        playerX = newX;
        playerY = newY;

        // Object interactions
        if (target == '*') {
            score++;
            map[newY][newX] = '.';
        }
        else if (target == 'E') {
            won = 1;
        }

        UpdateMap();
    }

    return 0;  // Continue normally
}

void LoadDefaultLevel() {
    memcpy(map, defaultMap, sizeof(defaultMap));
    playerX = defaultPlayerX;
    playerY = defaultPlayerY;
}

void LoadCustomLevel() {
    if (hasCustomLevel) {
        memcpy(map, customMap, sizeof(customMap));
        playerX = customPlayerX;
        playerY = customPlayerY;
    }
}

void PlayCurrentLevel() {
    score = 0;
    won = 0;
    DrawMap();

    while (!won) {
        if (MovePlayer() == 1) {
            break;  // User pressed Q to quit
        }
    }

    // If won, the final DrawMap already showed the congratulations
    if (won) {
        printf("\nPress any key to return to main menu...\n");
        getch();
    }
    // If quit, message was already shown inside MovePlayer()
}

int ShowMainMenu() {
    while (1) {
        system("cls");
        printf("======================================\n");
        printf("        HELHEIM ENGINE 2D v1.0\n");
        printf("======================================\n\n");
        printf("1. Play Default Level\n");
        printf("2. Create / Edit Custom Level\n");
        if (hasCustomLevel) {
            printf("3. Play Custom Level\n");
        } else {
            printf("3. Play Custom Level (no custom level yet)\n");
        }
        printf("4. Quit Game\n\n");
        printf("Press the number of your choice...\n");

        char choice = getch();
        if (choice == '1') return 1;
        if (choice == '2') return 2;
        if (choice == '3' && hasCustomLevel) return 3;
        if (choice == '4') return 4;
        // Invalid input -> loop and redraw menu
    }
}

void LevelEditor() {
    // Load base map for editing (custom if exists, otherwise default)
    if (hasCustomLevel) {
        memcpy(editorMap, customMap, sizeof(customMap));
        editorPlayerX = customPlayerX;
        editorPlayerY = customPlayerY;
    } else {
        memcpy(editorMap, defaultMap, sizeof(defaultMap));
        editorPlayerX = defaultPlayerX;
        editorPlayerY = defaultPlayerY;
    }

    int cursorX = editorPlayerX;
    int cursorY = editorPlayerY;

    while (1) {
        system("cls");

        // Draw editor map with cursor and player start
        for (int y = 0; y < HEIGHT; y++) {
            for (int x = 0; x < WIDTH; x++) {
                if (x == cursorX && y == cursorY) {
                    printf("+");  // Cursor
                } else if (x == editorPlayerX && y == editorPlayerY) {
                    printf("P");
                } else {
                    printf("%c", editorMap[y][x]);
                }
            }
            printf("\n");
        }

        printf("\n");
        printf("=== LEVEL EDITOR ===\n");
        printf("Cursor position: (%d, %d)\n", cursorX, cursorY);
        printf("Controls:\n");
        printf("W/A/S/D : Move cursor\n");
        printf("1 : Wall (#)    2 : Star (*)\n");
        printf("3 : Exit (E)    4 : Empty (.)\n");
        printf("5 : Set Player Start (P)\n");
        printf("ENTER : Save Custom Level\n");
        printf("Q : Quit Editor (back to menu)\n");
        printf("================================\n");

        char input = getch();

        int newCX = cursorX;
        int newCY = cursorY;

        switch (input) {
            case 'w': case 'W':
                newCY--;
                break;
            case 's': case 'S':
                newCY++;
                break;
            case 'a': case 'A':
                newCX--;
                break;
            case 'd': case 'D':
                newCX++;
                break;

            case '1':
                if (cursorX >= 0 && cursorX < WIDTH && cursorY >= 0 && cursorY < HEIGHT) {
                    editorMap[cursorY][cursorX] = '#';
                }
                break;
            case '2':
                if (cursorX >= 0 && cursorX < WIDTH && cursorY >= 0 && cursorY < HEIGHT) {
                    editorMap[cursorY][cursorX] = '*';
                }
                break;
            case '3':
                if (cursorX >= 0 && cursorX < WIDTH && cursorY >= 0 && cursorY < HEIGHT) {
                    editorMap[cursorY][cursorX] = 'E';
                }
                break;
            case '4':
                if (cursorX >= 0 && cursorX < WIDTH && cursorY >= 0 && cursorY < HEIGHT) {
                    editorMap[cursorY][cursorX] = '.';
                }
                break;
            case '5':
                editorPlayerX = cursorX;
                editorPlayerY = cursorY;
                break;

            case '\r':
                memcpy(customMap, editorMap, sizeof(editorMap));
                customPlayerX = editorPlayerX;
                customPlayerY = editorPlayerY;
                hasCustomLevel = 1;
                printf("\n>>> CUSTOM LEVEL SAVED SUCCESSFULLY! <<<\n");
                printf("You can now play it from the main menu.\n");
                getch();
                break;

            case 'q': case 'Q':
                printf("\nExiting editor...\n");
                getch();
                return;
        }

        // Clamp cursor to map bounds
        if (newCX >= 0 && newCX < WIDTH && newCY >= 0 && newCY < HEIGHT) {
            cursorX = newCX;
            cursorY = newCY;
        }
    }
}

int main() {
    InitializeDefaultMap();

    // Initialize custom map as blank
    ClearMap(customMap);
    customPlayerX = 1;
    customPlayerY = 1;
    hasCustomLevel = 0;

    // Main game engine loop
    while (1) {
        int choice = ShowMainMenu();

        if (choice == 1) {
            LoadDefaultLevel();
            PlayCurrentLevel();
        }
        else if (choice == 2) {
            LevelEditor();
        }
        else if (choice == 3) {
            LoadCustomLevel();
            PlayCurrentLevel();
        }
        else if (choice == 4) {
            system("cls");
            printf("Thanks for playing the Console Game Engine!\n");
            printf("Goodbye!\n");
            return 0;
        }
    }

    return 0;
}