#ifndef GAMEOBJECT_FACTORY_H
#define GAMEOBJECT_FACTORY_H

/*
 * Makes game objects with a specific
 * AI. Basically it pieces everything together :D
 */

#include <vector>
#include "constants.h"

#include "AI.h"

#include "BlasterEnemyAI.h"
#include "SpawnerAI.h"
#include "BulletAI.h"
#include "PlayerAI.h"
#include "MachineBlasterEnemyAI.h"
#include "BasicEnemyAI.h"
#include "ExplosionAI.h"
#include "AcidicBlockAI.h"
#include "AnimatedPropAI.h"
#include "GameObject.h"

class InputManager;
class GameObjectFactory{
	public:
		GameObjectFactory();
		~GameObjectFactory();

		GameObject *createPlayer(Point pos, Point size, InputManager* inputManager, std::string animationGroup = PlayerAnimationGroupName);
		GameObject *createBasicEnemy(Point pos, Point size, float maxSpeed, int health, float dmg, std::string animationGroup = BasicEnemyAnimationGroupName);
		GameObject *createBlasterEnemy(Point pos, Point size, float maxSpeed, int health, FireCommandBullet b, std::string animationGroup = BlasterEnemyAnimationGroupName);
		GameObject *createMGBlasterEnemy(Point pos, Point size, float maxSpeed, int health, FireCommandBullet b, std::string animationGroup = MachineBlasterEnemyAnimationGroupName);
		GameObject *createBullet(GameObject* owner, Point pos, Point size, Texture* tex, Point speed, float dmg, float pushForce, bool explosive=false, float explosionRadius=0);
		GameObject *createWall(Point pos, Point size, Texture* tex);
		GameObject *createAcid(Point pos, Point size, Texture* tex);
		GameObject *createExplosion(Point pos, float radius, float damage, std::string animationGroup);
		GameObject *createProp(Point pos, Point size, Texture* tex, bool gravity=false, bool collidable=false);
		GameObject *createSpawner(Point pos, int maxEntities, float spawnDelay, SpawnList& spawnList);
		GameObject *createAnimationProp(Point pos, Point size, std::string animationGroupName, float speed, int loops);

		FireCommandBullet generateRubberBullet(int forWho);
		FireCommandBullet generateLeadBullet(int forWho);
		FireCommandBullet generateSilverBullet(int forWho);
		FireCommandBullet generateGoldBullet(int forWho);
		FireCommandBullet generateMGBullet(int forWho);
		FireCommandBullet generateRocketBullet(int forWho);
		static GameObjectFactory* instance(){
			if(_instance == nullptr) _instance = new GameObjectFactory();
			return _instance;
		}	

		void deleteObject(int index){
			GameObject* goPtr = _gameObjects[index];
			AI* aiPtr = _aiList[index];
			_gameObjects.erase(_gameObjects.begin() + index);
			_aiList.erase(_aiList.begin() + index);
			delete goPtr;
			delete aiPtr;
		}
	private:
		std::vector<AI*> _aiList; // for deletion
		std::vector<GameObject*> _gameObjects;
		static GameObjectFactory* _instance;
};

#endif
