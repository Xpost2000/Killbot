#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include "constants.h"
#include "Renderer2D.h"

class GameObject;
class World{
	public:
		World();
		~World();

		void update(float dt);
		void draw(Renderer2D* renderer);
		
		void AddEntity(GameObject* obj);
		void ClearNonPlayerEntities();
		bool areAllSpawnersEmpty();
		int getEnemyCount();
		std::vector<GameObject*>& getEntities() { return _objs; }
	private:
		std::vector<GameObject*> _objs;
};

#endif
