#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "gameplay.h"
#include "globals.h"
#include "entity.h"
#include "tile.h"
#include "rendering.h"
#include "input.h"
#include "particle.h"
#include "utils.h"

void LoadDefaultLevel() {
    // Reset game state
    score = 0;
    health = maxHealth;
    won = 0;
    levelTime = 0;
    starsCollected = 0;
    totalStars = 0;
    screenCleared = 0;
    gameState = STATE_PLAYING;
    
    // Clear entities
    for (int i = 0; i < entityCount; i++) {
        if (entities[i].active) FreeEntity(&entities[i]);
    }
    entityCount = 0;
    particleCount = 0;
    player = NULL;  // Reset player pointer
    
    // Load map
    InitializeDefaultMap();
    
    // Create player
    player = CreateEntity(ENTITY_PLAYER, defaultPlayerX, defaultPlayerY, 'P');
    if (player) {
        player->health->health = health;
        map[defaultPlayerY][defaultPlayerX] = 'P';
    }
    
    // Create collectible entities from map
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (map[y][x] == '*') {
                Entity* collectible = CreateEntity(ENTITY_COLLECTIBLE, x, y, '*');
                if (collectible) {
                    collectible->collectibleValue = 10;
                }
            }
        }
    }
    
    // Add some enemies at safe spawn points to avoid overlap
    for (int i = 0; i < 3; i++) {
        int spawnX, spawnY;
        
        // Create diverse spawn points
        if (i == 0) {
            spawnX = 2;
            spawnY = 2;
        } else if (i == 1) {
            spawnX = WIDTH - 3;
            spawnY = 2;
        } else {
            spawnX = WIDTH / 2;
            spawnY = HEIGHT - 3;
        }
        
        // Avoid spawning on player, walls, or collectibles
        if (map[spawnY][spawnX] != '#' && map[spawnY][spawnX] != 'P' && map[spawnY][spawnX] != '*') {
            Entity* enemy = CreateEntity(ENTITY_ENEMY, spawnX, spawnY, 'G');
            if (enemy && enemy->behavior && enemy->health) {
                enemy->health->health = 30;
                enemy->behavior->visionRange = 5;
                enemy->behavior->state = 0;  // Idle state
                enemy->behavior->moveTimer = 0;
                enemy->behavior->moveDirection = 0;
                map[spawnY][spawnX] = 'G';
            }
        }
    }
}

void PlayCurrentLevel() {
    if (!player) {
        system("cls");
        printf("Error: Player not initialized!\n");
        printf("Press any key to continue...\n");
        getch();
        return;
    }
    
    long long lastFrameTime = GetCurrentTimeMS();
    long long levelStartTime = GetCurrentTimeMS();
    
    while (gameState == STATE_PLAYING) {
        long long currentTime = GetCurrentTimeMS();
        long long elapsed = currentTime - lastFrameTime;
        
        if (elapsed >= FRAME_TIME_MS) {
            // Update game logic
            UpdateEntities();
            UpdateParticles();
            
            // Handle input
            int inputResult = HandleInput();
            if (inputResult == -1) break;  // Quit to menu
            
            // Update level time
            levelTime = (int)((currentTime - levelStartTime) / 1000);
            
            // Render
            RenderGame();
            
            // Check game over conditions
            if (health <= 0) {
                gameState = STATE_GAMEOVER;
            } else if (won) {
                gameState = STATE_WON;
            }
            
            lastFrameTime = currentTime;
        }
    }
    
    // Show end screen
    ShowGameOverScreen();
}

void ShowGameOverScreen() {
    system("cls");
    if (won) {
        printf("╔════════════════════════════════════════╗\n");
        printf("║         *** YOU WIN! ***              ║\n");
        printf("║  Final Score: %-25d║\n", score);
        printf("║  Level Time: %d seconds             ║\n", levelTime);
        printf("║  Total Stars: %d / %d                ║\n", starsCollected, totalStars);
        printf("╚════════════════════════════════════════╝\n");
    } else {
        printf("╔════════════════════════════════════════╗\n");
        printf("║      *** GAME OVER ***               ║\n");
        printf("║  Final Score: %-25d║\n", score);
        printf("║  You ran out of health!              ║\n");
        printf("╚════════════════════════════════════════╝\n");
    }
    
    printf("\nPress any key to return to main menu...\n");
    getch();
}
