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
    
    // Load map
    InitializeDefaultMap();
    
    // Create player
    player = CreateEntity(ENTITY_PLAYER, defaultPlayerX, defaultPlayerY, 'P');
    if (player) {
        player->health->health = health;
        map[defaultPlayerY][defaultPlayerX] = 'P';
    }
    
    // Add some enemies
    for (int i = 0; i < 3; i++) {
        Entity* enemy = CreateEntity(ENTITY_ENEMY, 5 + i * 3, 5, 'G');
        if (enemy) {
            enemy->health->health = 30;
            enemy->behavior->visionRange = 5;
            map[5][5 + i * 3] = 'G';
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
        printf("║  Final Score: %-24d║\n", score);
        printf("║  Level Time: %d seconds             ║\n", levelTime);
        printf("║  Total Stars: %d / %d                ║\n", starsCollected, totalStars);
        printf("╚════════════════════════════════════════╝\n");
    } else {
        printf("╔════════════════════════════════════════╗\n");
        printf("║      *** GAME OVER ***               ║\n");
        printf("║  Final Score: %-24d║\n", score);
        printf("║  You ran out of health!              ║\n");
        printf("╚════════════════════════════════════════╝\n");
    }
    
    printf("\nPress any key to return to main menu...\n");
    getch();
}
