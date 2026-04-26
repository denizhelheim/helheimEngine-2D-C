#ifndef COLLISION_H
#define COLLISION_H

int CheckCollision(float x1, float y1, float w1, float h1,
                   float x2, float y2, float w2, float h2);
int IsWall(int x, int y);
int IsHazard(int x, int y);

#endif // COLLISION_H
