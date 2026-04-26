#include <stdio.h>
#include <windows.h>
#include "rendering.h"
#include "globals.h"

void SetCursorPosition(int x, int y) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = {(SHORT)x, (SHORT)y};
    SetConsoleCursorPosition(hConsole, coord);
}

void HideCursor() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(hConsole, &info);
}

void InitializeScreenBuffers() {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            screenBuffer[y][x] = '.';
            prevScreenBuffer[y][x] = ' ';
        }
    }
    consoleInitialized = 1;
}

void ClearGameScreen() {
    system("cls");
    screenCleared = 1;
}

// Fixed DrawGameUI with proper text alignment
void DrawGameUI() {
    // Only redraw if values changed
    if (lastDisplayedScore != score) {
        SetCursorPosition(9, HEIGHT + 4);
        printf("%7d                                ", score);
        lastDisplayedScore = score;
    }
    
    if (lastDisplayedHealth != health) {
        SetCursorPosition(9, HEIGHT + 5);
        printf("%3d / %3d                         ", health, maxHealth);
        lastDisplayedHealth = health;
    }
    
    if (lastDisplayedStars != starsCollected) {
        SetCursorPosition(9, HEIGHT + 6);
        printf("%d / %d                            ", starsCollected, totalStars);
        lastDisplayedStars = starsCollected;
    }
    
    if (lastDisplayedTime != levelTime) {
        SetCursorPosition(9, HEIGHT + 7);
        printf("%d seconds                           ", levelTime);
        lastDisplayedTime = levelTime;
    }
}

void RenderGame() {
    static int uiDrawn = 0;
    
    // Clear screen and draw UI frame on first call
    if (!screenCleared) {
        system("cls");
        screenCleared = 1;
        uiDrawn = 0;
        // Initialize previous buffer
        for (int y = 0; y < HEIGHT; y++) {
            for (int x = 0; x < WIDTH; x++) {
                prevScreenBuffer[y][x] = 0;
            }
        }
    }
    
    // Draw UI border/frame once
    if (!uiDrawn) {
        SetCursorPosition(0, HEIGHT + 1);
        printf("╔════════════════════════════════════════╗");
        SetCursorPosition(0, HEIGHT + 2);
        printf("║           HELHEIM ENGINE 2D v2.0       ║");
        SetCursorPosition(0, HEIGHT + 3);
        printf("╠════════════════════════════════════════╣");
        SetCursorPosition(0, HEIGHT + 4);
        printf("║ Score:                                  ║");
        SetCursorPosition(0, HEIGHT + 5);
        printf("║ Health:                                 ║");
        SetCursorPosition(0, HEIGHT + 6);
        printf("║ Stars:                                  ║");
        SetCursorPosition(0, HEIGHT + 7);
        printf("║ Level Time:                             ║");
        SetCursorPosition(0, HEIGHT + 8);
        printf("╠════════════════════════════════════════╣");
        SetCursorPosition(0, HEIGHT + 9);
        printf("║ W/A/S/D=Move | Space=Special | Q=Quit  ║");
        SetCursorPosition(0, HEIGHT + 10);
        printf("║ P=Pause | Diff: NORMAL                ║");
        SetCursorPosition(0, HEIGHT + 11);
        printf("╚════════════════════════════════════════╝");
        uiDrawn = 1;
    }
    
    // Build current frame buffer
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            int drawn = 0;
            
            // Check entities first
            for (int i = 0; i < entityCount; i++) {
                Entity* e = &entities[i];
                if (e->active && (int)e->position.x == x && (int)e->position.y == y) {
                    screenBuffer[y][x] = e->displayChar;
                    drawn = 1;
                    break;
                }
            }
            
            if (!drawn) {
                screenBuffer[y][x] = map[y][x];
            }
        }
    }
    
    // Only update changed cells
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (screenBuffer[y][x] != prevScreenBuffer[y][x]) {
                SetCursorPosition(x, y);
                printf("%c", screenBuffer[y][x]);
                prevScreenBuffer[y][x] = screenBuffer[y][x];
            }
        }
    }
    
    // Draw UI at fixed position
    DrawGameUI();
    
    if (gameState == STATE_PAUSED) {
        SetCursorPosition(6, HEIGHT + 12);
        printf("*** PAUSED ***");
    }
    fflush(stdout);
}

void DrawDebugInfo() {
    if (gameConfig.showDebugInfo) {
        SetCursorPosition(0, HEIGHT + 14);
        printf("[DEBUG] Entities: %d | Particles: %d            ", entityCount, particleCount);
    }
}
