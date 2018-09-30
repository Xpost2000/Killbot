#include "SpawnerAI.h"
#include "GameObject.h"
#include "RandomNumberGenerator.h"
#include "GameObjectFactory.h"

#include <iostream>

SpawnerAI::SpawnerAI(GameObject* parent, int maxEntities, float spawnDelay) : 
	AI(parent),
	_maxEntities(maxEntities),
       	_spawnDelayMax(spawnDelay),
	_spawnDelay( 0 ) {
}

SpawnerAI::~SpawnerAI(){
}

void SpawnerAI::update(float dt, World& world){
	if(_spawnDelay <= 0 && canSpawn()){
		_spawnDelay = _spawnDelayMax;
		_spawned++;
	// 	SPAWN HERE
	//
	//	The cloning function doesn't work. I believe I know why but it was much easier to store
	//	a lambda with a spawning function ( so basically this is really a scripted object being used as a spawner
	//	rather than an actual spawner itself. )
	//
	//	world.AddEntity(GameObjectFactory::instance()->makeClone(AI::getParent()->getPosition(), determineSpawn()));
	//
	//	TODO: Use like a spawn arguments system cause the clone function doesn't work.
	//	      Also I realized it really can't work in the way I tried it. I would have to cleverly change stuff if that were that case.
	//	world.AddEntity(GameObjectFactory::instance()->createBasicEnemy(AI::getParent()->getPosition(), Point{75, 75}, 85, 100));
	// 
	//	well a lambda works. It's kind of an odd form of cheating.
		determineSpawn()(AI::getParent()->getPosition());
	}else{
		_spawnDelay -= dt;
	}
}

void SpawnerAI::addToList( SpawnerType baseObject, int probability){
	_spawnList.push_back( std::make_pair(baseObject, probability) );
}

// using the weighted random system...
SpawnerType SpawnerAI::determineSpawn(){
	auto max_calc = [&]() -> int{ 
		int result = 0; 
		for(const auto& p : _spawnList) 
			{ result+=p.second; } 
		return result;
	};
	int target = RandomInt(0, max_calc())();
	for(const auto& p : _spawnList){
		if(target <= p.second){
			return p.first;
		}else{
			target -= p.second;
		}
	}
}
