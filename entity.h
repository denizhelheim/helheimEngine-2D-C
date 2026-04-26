#ifndef ENTITY_H
#define ENTITY_H

#include "types.h"

// Memory management
void InitializeEntity(Entity* entity);
void FreeEntity(Entity* entity);

// Entity system
Entity* CreateEntity(EntityType type, float x, float y, char displayChar);
void RemoveEntity(int index);
void UpdateEntities();
void UpdateEnemyAI(Entity* enemy);

#endif // ENTITY_H
