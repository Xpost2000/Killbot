#ifndef SPAWNERMACROS_H
#define SPAWNERMACROS_H

#include "GameObjectFactory.h"
#include <utility>
#include <functional>
/*
 * a set of functions to make functions. :D
 * this is for the SPAWNER. So it won't make an entity in the world
 * just use the standard create functions.
 *
 * TODO: actually make what I said I was going to make here.
 */

//#define BasicEnemy(size, speed, health, probability) std::make_pair([&](Point pos){world.AddEntity(GameObjectFactory::instance()->createBasicEnemy(pos, size, speed, health));}, probability)


#endif
