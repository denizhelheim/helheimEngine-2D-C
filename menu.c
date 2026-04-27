#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "menu.h"
#include "globals.h"
#include "entity.h"
#include "tile.h"

int ShowMainMenu() {
    while (1) {
        system("cls");
        printf("╔════════════════════════════════════════╗\n");
        printf("║    HELHEIM ENGINE 2D v2.0            ║\n");
        printf("║         PRO EDITION                   ║\n");
        printf("╠════════════════════════════════════════╣\n");
        printf("║                                        ║\n");
        printf("║  1. Play Default Level                ║\n");
        printf("║  2. Advanced Level Editor             ║\n");
        if (hasCustomLevel) {
            printf("║  3. Play Custom Level ✓              ║\n");
        } else {
            printf("║  3. Play Custom Level (create one)   ║\n");
        }
        printf("║  4. Difficulty Settings               ║\n");
        printf("║  5. Game Settings                     ║\n");
        printf("║  6. How to Play                       ║\n");
        printf("║  7. About                             ║\n");
        printf("║  0. Quit Game                         ║\n");
        printf("║                                        ║\n");
        printf("╚════════════════════════════════════════╝\n");
        printf("\nPress the number of your choice...\n");
        
        char choice = getch();
        
        switch (choice) {
            case '1': return 1;
            case '2': return 2;
            case '3': return (hasCustomLevel ? 3 : 0);
            case '4': return 4;
            case '5': return 5;
            case '6': return 6;
            case '7': return 7;
            case '0': return 0;
        }
    }
}

void AdvancedLevelEditor() {
    // Clear old entities
    for (int i = 0; i < entityCount; i++) {
        if (entities[i].active) FreeEntity(&entities[i]);
    }
    entityCount = 0;
    
    ClearMap(map);
    InitializeTileMap();
    
    int cursorX = 5, cursorY = 5;
    int editorPlayerX = 1, editorPlayerY = 1;
    int editMode = 0;  // 0: tiles, 1: entities
    
    while (1) {
        system("cls");
        
        // Draw map with cursor
        for (int y = 0; y < HEIGHT; y++) {
            for (int x = 0; x < WIDTH; x++) {
                if (x == cursorX && y == cursorY) {
                    printf("+");
                } else if (x == editorPlayerX && y == editorPlayerY) {
                    printf("P");
                } else {
                    printf("%c", map[y][x]);
                }
            }
            printf("\n");
        }
        
        printf("\n╔════════════════════════════════════════╗\n");
        printf("║         ADVANCED LEVEL EDITOR         ║\n");
        printf("╠════════════════════════════════════════╣\n");
        printf("║ Cursor: (%2d, %2d) Mode: %s          ║\n", 
               cursorX, cursorY, editMode ? "ENTITIES" : "TILES    ");
        printf("║                                        ║\n");
        printf("║ Movement: W/A/S/D                      ║\n");
        printf("║ TILE MODE (T):                         ║\n");
        printf("║  1=Wall(#) 2=Lava(~) 3=Ice(=) 4=Exit  ║\n");
        printf("║  5=Empty(.) 6=Spawn(S)                ║\n");
        printf("║ ENTITY MODE (E):                       ║\n");
        printf("║  1=Star(*) 2=Enemy(G) 3=Hazard        ║\n");
        printf("║ P: Set player start     T/E: Mode     ║\n");
        printf("║ ENTER: Save  Q: Quit                   ║\n");
        printf("╚════════════════════════════════════════╝\n");
        
        char input = getch();
        
        int newX = cursorX, newY = cursorY;
        
        switch (input) {
            case 'w': case 'W': newY--; break;
            case 's': case 'S': newY++; break;
            case 'a': case 'A': newX--; break;
            case 'd': case 'D': newX++; break;
            
            case 't': case 'T':
                editMode = 0;
                break;
            case 'e': case 'E':
                editMode = 1;
                break;
            
            case 'p': case 'P':
                editorPlayerX = cursorX;
                editorPlayerY = cursorY;
                break;
            
            // Tile mode
            case '1':
                if (!editMode) {
                    SetTile(cursorX, cursorY, TILE_WALL);
                    map[cursorY][cursorX] = '#';
                }
                break;
            case '2':
                if (!editMode) {
                    SetTile(cursorX, cursorY, TILE_LAVA);
                    map[cursorY][cursorX] = '~';
                }
                break;
            case '3':
                if (!editMode) {
                    SetTile(cursorX, cursorY, TILE_ICE);
                    map[cursorY][cursorX] = '=';
                }
                break;
            case '4':
                if (!editMode) {
                    SetTile(cursorX, cursorY, TILE_EXIT);
                    map[cursorY][cursorX] = 'E';
                }
                break;
            case '5':
                if (!editMode) {
                    SetTile(cursorX, cursorY, TILE_EMPTY);
                    map[cursorY][cursorX] = '.';
                }
                break;
            case '6':
                if (!editMode) {
                    SetTile(cursorX, cursorY, TILE_SPAWN);
                    map[cursorY][cursorX] = 'S';
                }
                break;
            
            // Entity mode
            case '!':  // Shift+1
                if (editMode && entityCount < MAX_ENTITIES) {
                    Entity* star = CreateEntity(ENTITY_COLLECTIBLE, cursorX, cursorY, '*');
                    if (star) {
                        star->collectibleValue = 10;
                        map[cursorY][cursorX] = '*';
                    }
                }
                break;
            case '@':  // Shift+2
                if (editMode && entityCount < MAX_ENTITIES) {
                    Entity* enemy = CreateEntity(ENTITY_ENEMY, cursorX, cursorY, 'G');
                    if (enemy && enemy->behavior) {
                        enemy->health->health = 30;
                        enemy->behavior->visionRange = 5;
                        enemy->behavior->state = 0;
                        enemy->behavior->moveTimer = 0;
                        map[cursorY][cursorX] = 'G';
                    }
                }
                break;
            
            case '\r':  // ENTER
                // Save level
                defaultPlayerX = editorPlayerX;
                defaultPlayerY = editorPlayerY;
                hasCustomLevel = 1;
                
                system("cls");
                printf("╔════════════════════════════════════════╗\n");
                printf("║    *** LEVEL SAVED SUCCESSFULLY! ***   ║\n");
                printf("║  You can now play it from the menu.    ║\n");
                printf("╚════════════════════════════════════════╝\n");
                printf("\nPress any key to continue...\n");
                getch();
                return;
            
            case 'q': case 'Q':
                return;
        }
        
        if (newX >= 0 && newX < WIDTH && newY >= 0 && newY < HEIGHT) {
            cursorX = newX;
            cursorY = newY;
        }
    }
}

void DifficultyMenu() {
    while (1) {
        system("cls");
        printf("╔════════════════════════════════════════╗\n");
        printf("║        SELECT DIFFICULTY LEVEL        ║\n");
        printf("╠════════════════════════════════════════╣\n");
        printf("║                                        ║\n");
        printf("║  1. EASY                              ║\n");
        printf("║     More health, fewer enemies       ║\n");
        printf("║                                        ║\n");
        printf("║  2. NORMAL (Recommended)               ║\n");
        printf("║     Balanced gameplay                 ║\n");
        printf("║                                        ║\n");
        printf("║  3. HARD                              ║\n");
        printf("║     Less health, many enemies        ║\n");
        printf("║                                        ║\n");
        printf("║  Q. Back to Menu                       ║\n");
        printf("║                                        ║\n");
        printf("╚════════════════════════════════════════╝\n");
        
        char choice = getch();
        
        if (choice == '1') {
            gameConfig.difficulty = DIFFICULTY_EASY;
            maxHealth = 150;
            // Sync current health if game is running
            if (gameState == STATE_PLAYING && health > maxHealth) {
                health = maxHealth;
            }
            return;
        }
        else if (choice == '2') {
            gameConfig.difficulty = DIFFICULTY_NORMAL;
            maxHealth = 100;
            if (gameState == STATE_PLAYING && health > maxHealth) {
                health = maxHealth;
            }
            return;
        }
        else if (choice == '3') {
            gameConfig.difficulty = DIFFICULTY_HARD;
            maxHealth = 50;
            if (gameState == STATE_PLAYING && health > maxHealth) {
                health = maxHealth;
            }
            return;
        }
        else if (choice == 'q' || choice == 'Q') {
            return;
        }
    }
}

void SettingsMenu() {
    while (1) {
        system("cls");
        printf("╔════════════════════════════════════════╗\n");
        printf("║          GAME SETTINGS                ║\n");
        printf("╠════════════════════════════════════════╣\n");
        printf("║                                        ║\n");
        printf("║  1. Particles: %s                    ║\n",
               gameConfig.enableParticles ? "ON " : "OFF");
        printf("║                                        ║\n");
        printf("║  2. Animations: %s                   ║\n",
               gameConfig.enableAnimations ? "ON " : "OFF");
        printf("║                                        ║\n");
        printf("║  3. Debug Info: %s                   ║\n",
               gameConfig.showDebugInfo ? "ON " : "OFF");
        printf("║                                        ║\n");
        printf("║  4. Difficulty: %s              ║\n",
               gameConfig.difficulty == DIFFICULTY_EASY ? "EASY  " :
               gameConfig.difficulty == DIFFICULTY_NORMAL ? "NORMAL" : "HARD  ");
        printf("║                                        ║\n");
        printf("║  Q. Back to Menu                       ║\n");
        printf("║                                        ║\n");
        printf("╚════════════════════════════════════════╝\n");
        
        char choice = getch();
        
        if (choice == '1') {
            gameConfig.enableParticles = !gameConfig.enableParticles;
        }
        else if (choice == '2') {
            gameConfig.enableAnimations = !gameConfig.enableAnimations;
        }
        else if (choice == '3') {
            gameConfig.showDebugInfo = !gameConfig.showDebugInfo;
        }
        else if (choice == '4') {
            DifficultyMenu();
        }
        else if (choice == 'q' || choice == 'Q') {
            return;
        }
    }
}

void TutorialMenu() {
    system("cls");
    printf("╔════════════════════════════════════════╗\n");
    printf("║         HOW TO PLAY                   ║\n");
    printf("╠════════════════════════════════════════╣\n");
    printf("║                                        ║\n");
    printf("║ OBJECTIVE:                             ║\n");
    printf("║  Collect all stars (*) and reach exit ║\n");
    printf("║  (E) to win the level!                ║\n");
    printf("║                                        ║\n");
    printf("║ CONTROLS:                              ║\n");
    printf("║  W/A/S/D - Move your character (P)    ║\n");
    printf("║  P - Pause/Resume game                ║\n");
    printf("║  Q - Quit to menu                     ║\n");
    printf("║  SPACE - Special action               ║\n");
    printf("║                                        ║\n");
    printf("║ MECHANICS:                             ║\n");
    printf("║  Stars (*) = +10 points               ║\n");
    printf("║  Walls (#) = Impassable               ║\n");
    printf("║  Lava (~) = Hazard (-5 health)       ║\n");
    printf("║  Ice (=) = Slippery terrain           ║\n");
    printf("║  Enemies (G) = Avoid or fight         ║\n");
    printf("║                                        ║\n");
    printf("║ Press any key to return...             ║\n");
    printf("║                                        ║\n");
    printf("╚════════════════════════════════════════╝\n");
    getch();
}

void CreditsMenu() {
    system("cls");
    printf("╔════════════════════════════════════════╗\n");
    printf("║  HELHEIM ENGINE 2D v2.0 (Pro Edition) ║\n");
    printf("╠════════════════════════════════════════╣\n");
    printf("║                                        ║\n");
    printf("║ A Professional 2D Game Engine          ║\n");
    printf("║ Built with C                           ║\n");
    printf("║                                        ║\n");
    printf("║ FEATURES:                              ║\n");
    printf("║  - Advanced Entity System              ║\n");
    printf("║  - Particle Effects                    ║\n");
    printf("║  - Enemy AI & Pathfinding              ║\n");
    printf("║  - Physics & Collision Detection      ║\n");
    printf("║  - Animation System                    ║\n");
    printf("║  - Inventory Management                ║\n");
    printf("║  - Level Editor                        ║\n");
    printf("║  - Multiple Difficulty Modes           ║\n");
    printf("║  - Game Configuration                  ║\n");
    printf("║  - Event/Trigger System                ║\n");
    printf("║                                        ║\n");
    printf("║ Ready for professional game dev!       ║\n");
    printf("║                                        ║\n");
    printf("║ Press any key to return...             ║\n");
    printf("║                                        ║\n");
    printf("╚════════════════════════════════════════╝\n");
    getch();
}
