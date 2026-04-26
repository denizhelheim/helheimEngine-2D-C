#include "particle.h"
#include "globals.h"

void EmitParticle(float x, float y, char displayChar, float velX, float velY, int lifetime) {
    if (particleCount >= MAX_PARTICLES) return;
    
    Particle* p = &particles[particleCount++];
    p->position.x = x;
    p->position.y = y;
    p->displayChar = displayChar;
    p->velocity.x = velX;
    p->velocity.y = velY;
    p->lifetime = lifetime;
    p->maxLifetime = lifetime;
    p->active = 1;
}

void UpdateParticles() {
    for (int i = 0; i < particleCount; i++) {
        if (!particles[i].active) continue;
        
        Particle* p = &particles[i];
        p->lifetime--;
        
        if (p->lifetime <= 0) {
            p->active = 0;
            continue;
        }
        
        p->position.x += p->velocity.x;
        p->position.y += p->velocity.y;
    }
}

void DrawParticles() {
    for (int i = 0; i < particleCount; i++) {
        if (!particles[i].active) continue;
        
        Particle* p = &particles[i];
        int px = (int)p->position.x;
        int py = (int)p->position.y;
        
        if (px >= 0 && px < WIDTH && py >= 0 && py < HEIGHT) {
            // Find what's at this position
            for (int j = 0; j < entityCount; j++) {
                if (entities[j].active && 
                    (int)entities[j].position.x == px && 
                    (int)entities[j].position.y == py) {
                    continue;  // Don't overwrite entities
                }
            }
        }
    }
}
