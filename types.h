#ifndef TYPES_H
#define TYPES_H

// ===== DEFINES =====
#define WIDTH 20
#define HEIGHT 20
#define MAX_ENTITIES 100
#define MAX_PARTICLES 500
#define MAX_COLLECTIBLES 20
#define MAX_ENEMIES 15
#define MAX_INVENTORY 10
#define ANIMATION_SPEED 3

// ===== ENUMS =====
typedef enum { ENTITY_PLAYER, ENTITY_ENEMY, ENTITY_COLLECTIBLE, ENTITY_HAZARD } EntityType;
typedef enum { TILE_EMPTY, TILE_WALL, TILE_SPAWN, TILE_EXIT, TILE_LAVA, TILE_ICE } TileType;
typedef enum { STATE_MENU, STATE_PLAYING, STATE_EDITOR, STATE_PAUSED, STATE_GAMEOVER, STATE_WON } GameState;
typedef enum { DIFFICULTY_EASY, DIFFICULTY_NORMAL, DIFFICULTY_HARD } Difficulty;

// ===== STRUCTURES =====

// Vector2D for positions and velocities
typedef struct {
    float x, y;
} Vector2;

// Entity Component - Animation
typedef struct {
    char frames[5];
    int frameCount;
    int currentFrame;
    int animationTimer;
    int isAnimating;
} AnimationComponent;

// Entity Component - Physics
typedef struct {
    Vector2 velocity;
    int hasGravity;
    int isColliding;
    int mass;
} PhysicsComponent;

// Entity Component - Health
typedef struct {
    int health;
    int maxHealth;
    int invulnerableTimer;
    int isDead;
} HealthComponent;

// Entity Component - Behavior (AI)
typedef struct {
    int state;  // 0: idle, 1: patrol, 2: chase, 3: attack
    int visionRange;
    int moveDirection;
    int moveTimer;
    int targetX, targetY;
} BehaviorComponent;

// Game Entity
typedef struct {
    int active;
    EntityType type;
    Vector2 position;
    Vector2 size;
    char displayChar;
    int layer;
    
    // Components
    AnimationComponent* animation;
    PhysicsComponent* physics;
    HealthComponent* health;
    BehaviorComponent* behavior;
    
    // Custom data
    int collectibleValue;
    int hazardDamage;
    int enemyAI;
} Entity;

// Particle System
typedef struct {
    Vector2 position;
    Vector2 velocity;
    char displayChar;
    int lifetime;
    int maxLifetime;
    int active;
} Particle;

// Inventory Item
typedef struct {
    char name[32];
    int quantity;
    int effect;
} InventoryItem;

// Game Configuration
typedef struct {
    Difficulty difficulty;
    int showDebugInfo;
    int enableParticles;
    int enableAnimations;
    int soundEffectsEnabled;
} GameConfig;

// Tile data
typedef struct {
    TileType type;
    int walkable;
    char displayChar;
} TileData;

#endif // TYPES_H
