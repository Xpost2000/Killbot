#ifndef SPAWNER_AI_H
#define SPAWNER_AI_H
#include "AI.h"
#include <functional>
#include <vector>
#include <utility>

typedef std::function<void(Point pos)> SpawnerType;
typedef std::vector< std::pair<SpawnerType, int> > SpawnList;

class SpawnerAI : public AI{
	public:
		SpawnerAI(GameObject* parent, int maxEntities, float spawnDelay);
		~SpawnerAI();

		void update(float dt, World& world);
		void addToList( SpawnerType baseObject, int probability);
		bool canSpawn() { return (_spawned < _maxEntities); }
		SpawnList& getSpawnList() { return _spawnList; }
	private:
		SpawnerType determineSpawn();
		SpawnList _spawnList;

		int _maxEntities = 0;
		int _spawned = 0;
		float _spawnDelay = 0;
		float _spawnDelayMax = 0;
};

#endif
