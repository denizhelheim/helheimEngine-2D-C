#ifndef PARTICLE_H
#define PARTICLE_H

#include "types.h"

void EmitParticle(float x, float y, char displayChar, float velX, float velY, int lifetime);
void UpdateParticles();
void DrawParticles();

#endif // PARTICLE_H
