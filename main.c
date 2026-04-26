#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "globals.h"
#include "rendering.h"
#include "tile.h"
#include "gameplay.h"
#include "menu.h"

int main() {
    // Enable UTF-8 support in Windows console
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    
    // Initialize rendering system
    HideCursor();
    InitializeScreenBuffers();
    
    srand((unsigned)time(NULL));
    
    // Initialize everything
    InitializeTileMap();
    InitializeDefaultMap();
    
    // Game loop
    while (1) {
        int menuChoice = ShowMainMenu();
        
        if (menuChoice == 0) {
            // Quit
            system("cls");
            printf("╔════════════════════════════════════════╗\n");
            printf("║   Thanks for playing with Helheim!    ║\n");
            printf("║        Engine 2D v2.0                 ║\n");
            printf("║                                        ║\n");
            printf("║  Make amazing games!                   ║\n");
            printf("╚════════════════════════════════════════╝\n\n");
            return 0;
        }
        else if (menuChoice == 1) {
            LoadDefaultLevel();
            PlayCurrentLevel();
        }
        else if (menuChoice == 2) {
            AdvancedLevelEditor();
        }
        else if (menuChoice == 3) {
            LoadDefaultLevel();
            PlayCurrentLevel();
        }
        else if (menuChoice == 4) {
            DifficultyMenu();
        }
        else if (menuChoice == 5) {
            SettingsMenu();
        }
        else if (menuChoice == 6) {
            TutorialMenu();
        }
        else if (menuChoice == 7) {
            CreditsMenu();
        }
    }
    
    return 0;
}
