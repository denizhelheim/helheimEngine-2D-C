#include <conio.h>
#include <math.h>
#include "input.h"
#include "globals.h"
#include "particle.h"

int MovePlayerTo(int newX, int newY) {
    if (!player) return 0;
    
    // Check boundaries
    if (newX < 0 || newX >= WIDTH || newY < 0 || newY >= HEIGHT) return 0;
    
    // Check walls (IsWall check)
    if (map[newY][newX] == '#' || tileMap[newY][newX].type == TILE_WALL) return 0;
    
    player->position.x = newX;
    player->position.y = newY;
    
    // Check for collectibles
    for (int i = 0; i < entityCount; i++) {
        Entity* e = &entities[i];
        if (e->active && e->type == ENTITY_COLLECTIBLE &&
            (int)e->position.x == newX && (int)e->position.y == newY) {
            score += e->collectibleValue;
            starsCollected++;
            e->active = 0;
            map[newY][newX] = '.';  // Clear from map
            
            if (gameConfig.enableParticles) {
                for (int p = 0; p < 5; p++) {
                    float angle = (p / 5.0f) * 6.28f;
                    EmitParticle(newX, newY, '*', cos(angle) * 0.2f, sin(angle) * 0.2f, 10);
                }
            }
        }
    }
    
    // Check for enemies
    for (int i = 0; i < entityCount; i++) {
        Entity* e = &entities[i];
        if (e->active && e->type == ENTITY_ENEMY &&
            (int)e->position.x == newX && (int)e->position.y == newY) {
            if (health > 0) {
                health -= 10;
                player->health->invulnerableTimer = 20;
            }
        }
    }
    
    // Check for exit
    if (map[newY][newX] == 'E') {
        won = 1;
        return 2;  // Won signal
    }
    
    // Check hazards
    if (tileMap[newY][newX].type == TILE_LAVA) {
        health -= 5;
    }
    
    return 1;
}

int HandleInput() {
    if (!_kbhit()) return 0;
    
    char input = getch();
    int newX = (int)player->position.x;
    int newY = (int)player->position.y;
    
    switch (input) {
        case 'w': case 'W':
            newY--;
            break;
        case 's': case 'S':
            newY++;
            break;
        case 'a': case 'A':
            newX--;
            break;
        case 'd': case 'D':
            newX++;
            break;
        case 'p': case 'P':
            gameState = (gameState == STATE_PAUSED) ? STATE_PLAYING : STATE_PAUSED;
            return 0;
        case 'q': case 'Q':
            gameState = STATE_MENU;
            return -1;
        case ' ':
            // Special action
            return 0;
        default:
            return 0;
    }
    
    if (gameState == STATE_PLAYING) {
        return MovePlayerTo(newX, newY);
    }
    
    return 0;
}
