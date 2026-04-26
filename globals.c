#include <stddef.h>
#include "globals.h"

// ===== GLOBAL VARIABLES =====

// Core game state
GameState gameState = STATE_MENU;
GameConfig gameConfig = {DIFFICULTY_NORMAL, 0, 1, 1, 0};
int gameTick = 0;

// Console buffers for flicker-free rendering
char screenBuffer[HEIGHT][WIDTH];
char prevScreenBuffer[HEIGHT][WIDTH];
int consoleInitialized = 0;
int screenCleared = 0;

// Map and tile system
char map[HEIGHT][WIDTH];
TileData tileMap[HEIGHT][WIDTH];
int defaultPlayerX = 1, defaultPlayerY = 1;
int customPlayerX = 1, customPlayerY = 1;
int hasCustomLevel = 0;

// Entity system
Entity entities[MAX_ENTITIES];
int entityCount = 0;
Entity* player = NULL;

// Particle system
Particle particles[MAX_PARTICLES];
int particleCount = 0;

// Game variables
int score = 0;
int health = 100;
int maxHealth = 100;
int won = 0;
int levelTime = 0;
int starsCollected = 0;
int totalStars = 0;
int lastDisplayedScore = -1;
int lastDisplayedHealth = -1;
int lastDisplayedStars = -1;
int lastDisplayedTime = -1;

// Frame timing
const int TARGET_FPS = 20;
const int FRAME_TIME_MS = 50;

// Inventory
InventoryItem inventory[MAX_INVENTORY];
int inventoryCount = 0;
