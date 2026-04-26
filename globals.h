#ifndef GLOBALS_H
#define GLOBALS_H

#include "types.h"

// ===== GLOBAL VARIABLES =====

// Core game state
extern GameState gameState;
extern GameConfig gameConfig;
extern int gameTick;

// Console buffers for flicker-free rendering
extern char screenBuffer[HEIGHT][WIDTH];
extern char prevScreenBuffer[HEIGHT][WIDTH];
extern int consoleInitialized;
extern int screenCleared;

// Map and tile system
extern char map[HEIGHT][WIDTH];
extern TileData tileMap[HEIGHT][WIDTH];
extern int defaultPlayerX, defaultPlayerY;
extern int customPlayerX, customPlayerY;
extern int hasCustomLevel;

// Entity system
extern Entity entities[MAX_ENTITIES];
extern int entityCount;
extern Entity* player;

// Particle system
extern Particle particles[MAX_PARTICLES];
extern int particleCount;

// Game variables
extern int score;
extern int health;
extern int maxHealth;
extern int won;
extern int levelTime;
extern int starsCollected;
extern int totalStars;
extern int lastDisplayedScore;
extern int lastDisplayedHealth;
extern int lastDisplayedStars;
extern int lastDisplayedTime;

// Frame timing
extern const int TARGET_FPS;
extern const int FRAME_TIME_MS;

// Inventory
extern InventoryItem inventory[MAX_INVENTORY];
extern int inventoryCount;

#endif // GLOBALS_H
