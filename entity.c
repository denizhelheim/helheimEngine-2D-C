#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "entity.h"
#include "globals.h"

// Forward declaration
void UpdateEnemyAI(Entity* enemy);

void InitializeEntity(Entity* entity) {
    entity->active = 0;
    entity->animation = malloc(sizeof(AnimationComponent));
    if (entity->animation) memset(entity->animation, 0, sizeof(AnimationComponent));
    entity->physics = malloc(sizeof(PhysicsComponent));
    if (entity->physics) memset(entity->physics, 0, sizeof(PhysicsComponent));
    entity->health = malloc(sizeof(HealthComponent));
    if (entity->health) memset(entity->health, 0, sizeof(HealthComponent));
    entity->behavior = malloc(sizeof(BehaviorComponent));
    if (entity->behavior) memset(entity->behavior, 0, sizeof(BehaviorComponent));
}

void FreeEntity(Entity* entity) {
    if (entity->animation) free(entity->animation);
    if (entity->physics) free(entity->physics);
    if (entity->health) free(entity->health);
    if (entity->behavior) free(entity->behavior);
}

Entity* CreateEntity(EntityType type, float x, float y, char displayChar) {
    if (entityCount >= MAX_ENTITIES) return NULL;
    
    Entity* entity = &entities[entityCount];
    InitializeEntity(entity);
    
    entity->active = 1;
    entity->type = type;
    entity->position.x = x;
    entity->position.y = y;
    entity->displayChar = displayChar;
    entity->size.x = 1;
    entity->size.y = 1;
    entity->layer = 0;
    
    // Initialize components
    entity->animation->frameCount = 1;
    entity->animation->currentFrame = 0;
    entity->animation->isAnimating = 0;
    entity->physics->velocity.x = 0;
    entity->physics->velocity.y = 0;
    entity->physics->mass = 1;
    entity->health->health = 100;
    entity->health->maxHealth = 100;
    entity->health->invulnerableTimer = 0;
    
    entityCount++;
    return entity;
}

void RemoveEntity(int index) {
    if (index < 0 || index >= entityCount) return;
    entities[index].active = 0;
}

void UpdateEntities() {
    for (int i = 0; i < entityCount; i++) {
        if (!entities[i].active) continue;
        
        Entity* e = &entities[i];
        
        // Update animation
        if (e->animation->isAnimating) {
            e->animation->animationTimer++;
            if (e->animation->animationTimer >= ANIMATION_SPEED) {
                e->animation->currentFrame = (e->animation->currentFrame + 1) % e->animation->frameCount;
                e->animation->animationTimer = 0;
            }
            e->displayChar = e->animation->frames[e->animation->currentFrame];
        }
        
        // Update invulnerability
        if (e->health->invulnerableTimer > 0) {
            e->health->invulnerableTimer--;
        }
        
        // Update enemy AI
        if (e->type == ENTITY_ENEMY && e->behavior) {
            UpdateEnemyAI(e);
        }
    }
}

void UpdateEnemyAI(Entity* enemy) {
    if (!enemy->behavior) return;
    
    BehaviorComponent* behavior = enemy->behavior;
    behavior->moveTimer++;
    
    // Simple patrol AI
    if (behavior->state == 0) {  // Idle
        if (behavior->moveTimer > 30) {
            behavior->state = 1;  // Switch to patrol
            behavior->moveTimer = 0;
            behavior->moveDirection = rand() % 4;
        }
    } else if (behavior->state == 1) {  // Patrol
        if (behavior->moveTimer % 5 == 0) {
            int oldX = (int)enemy->position.x;
            int oldY = (int)enemy->position.y;
            int newX = oldX;
            int newY = oldY;
            
            switch (behavior->moveDirection) {
                case 0: newY--; break;  // Up
                case 1: newY++; break;  // Down
                case 2: newX--; break;  // Left
                case 3: newX++; break;  // Right
            }
            
            // Check boundaries and walls
            if (newX >= 0 && newX < WIDTH && newY >= 0 && newY < HEIGHT && 
                map[newY][newX] != '#' && map[newY][newX] != 'P') {
                // Clear old position
                if (map[oldY][oldX] == 'G') map[oldY][oldX] = '.';
                
                enemy->position.x = newX;
                enemy->position.y = newY;
                
                // Update new position
                map[newY][newX] = 'G';
            } else {
                behavior->moveDirection = rand() % 4;
            }
        }
        
        if (behavior->moveTimer > 60) {
            behavior->state = 0;
            behavior->moveTimer = 0;
        }
    } else if (behavior->state == 2) {  // Chase
        if (behavior->moveTimer % 3 == 0) {
            int oldX = (int)enemy->position.x;
            int oldY = (int)enemy->position.y;
            int newX = oldX;
            int newY = oldY;
            
            // Move towards player
            if (player) {
                int playerX = (int)player->position.x;
                int playerY = (int)player->position.y;
                
                if (abs(playerX - oldX) > abs(playerY - oldY)) {
                    // Closer in X direction
                    newX = (playerX > oldX) ? oldX + 1 : oldX - 1;
                } else {
                    // Closer in Y direction
                    newY = (playerY > oldY) ? oldY + 1 : oldY - 1;
                }
            }
            
            // Check boundaries and walls before moving
            if (newX >= 0 && newX < WIDTH && newY >= 0 && newY < HEIGHT && 
                map[newY][newX] != '#') {
                // Clear old position
                if (map[oldY][oldX] == 'G') map[oldY][oldX] = '.';
                
                enemy->position.x = newX;
                enemy->position.y = newY;
                
                // Update new position
                map[newY][newX] = 'G';
            }
        }
        
        // Check if player is still in vision range
        if (player) {
            float distX = player->position.x - enemy->position.x;
            float distY = player->position.y - enemy->position.y;
            float distance = sqrt(distX * distX + distY * distY);
            
            if (distance >= behavior->visionRange + 2) {
                behavior->state = 1;  // Return to patrol
                behavior->moveTimer = 0;
                behavior->moveDirection = rand() % 4;
            }
        }
    }
    
    // Check for player collision (vision range)
    if (player) {
        float distX = player->position.x - enemy->position.x;
        float distY = player->position.y - enemy->position.y;
        float distance = sqrt(distX * distX + distY * distY);
        
        if (distance < behavior->visionRange) {
            behavior->state = 2;  // Chase
            behavior->targetX = (int)player->position.x;
            behavior->targetY = (int)player->position.y;
        }
    }
}
