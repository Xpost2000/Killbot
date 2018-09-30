#ifndef PARTICLE_H
#define PARTICLE_H

#include "Point.h"
#include "Color.h"

typedef struct Particle{
	float lifeTime;
	Point position, size;
	Color color;
}Particle;

#endif
