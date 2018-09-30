#include "World.h"
#include "GameObject.h"
#include "GameObjectFactory.h"

#include <cstdio>

World::World(){
}

World::~World(){
}

void World::ClearNonPlayerEntities(){
	for(int i = 0; i < _objs.size(); ++i){
		if(_objs[i]->deletable && _objs[i]->getType() != GameObjectTypePlayer){
			_objs.erase(_objs.begin() + i);
			GameObjectFactory::instance()->deleteObject(i);
		}
	}
}

void World::update(float dt){
	for(int i = 0; i < _objs.size(); ++i){
		if(_objs[i]->getHealth() <= 0){
			if(_objs[i]->deletable && _objs[i]->getType() != GameObjectTypePlayer){
				_objs.erase(_objs.begin() + i);
				//GameObjectFactory::instance()->deleteObject(i);
				//ok so clean up things afterwards, like just mark it in a TO_DELETE list
				//or something like that. Just incase shit breaks.
			}
		}
	}

	for(int i = 0; i < _objs.size(); ++i){
		if(_objs[i] != nullptr)
		_objs[i]->update(dt, *this);

		// "kill" an object.
		// TODO: add deletable flag.
	}
}

void World::draw(Renderer2D* renderer){
	for(int i = 0; i < _objs.size(); ++i){
		_objs[i]->draw(renderer);
	}
}
	
void World::AddEntity(GameObject* obj){
	_objs.push_back(obj);
}

int World::getEnemyCount(){
	int count = 0;
	for(auto &e : _objs){
		if(e->getType() == GameObjectTypeEnemy){
			count++;
		}
	}
	return count;
}

bool World::areAllSpawnersEmpty(){
	bool result = true;
	for(auto & e : _objs){
		if(e->getType() == GameObjectTypeSpawner){
			SpawnerAI* cast = (SpawnerAI*)e->getAI();
			result = !cast->canSpawn();
		}
	}
	return result;
}

