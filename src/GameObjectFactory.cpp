#include "GameObjectFactory.h"

GameObjectFactory* GameObjectFactory::_instance = nullptr;

GameObjectFactory::GameObjectFactory(){

}

GameObjectFactory::~GameObjectFactory(){
	for(auto& objs : _gameObjects){
		delete objs;
	}
	for(auto& ai : _aiList){
		delete ai;
	}
}

GameObject *GameObjectFactory::createPlayer(Point pos, Point size, InputManager* inputManager, std::string animationGroup){
	GameObject *newPlayer = new GameObject(pos, size);
	AI* newAi = new PlayerAI(newPlayer, inputManager, animationGroup);
	newPlayer->setAI(newAi);
	newPlayer->getHealth() = 50;
	newPlayer->getMaxHealth() = 50;
	newPlayer->_magicNumberType = GameObjectTypePlayer;

	_gameObjects.push_back(newPlayer);
	_aiList.push_back(newAi);
	return newPlayer;
}

// well it's really a dummy object, but same thing :D
GameObject *GameObjectFactory::createWall(Point pos, Point size, Texture* tex){
	GameObject* newWall = new GameObject(pos, size);
	newWall->setTexture(tex);
	newWall->gravityEnabled = false;
	newWall->collidable = true;
	newWall->deletable = true;
	newWall->_magicNumberType = GameObjectTypeBlock;

	_gameObjects.push_back(newWall);
	_aiList.push_back(new AI(nullptr)); // cheap way to prevent crashes
	return newWall;
}

GameObject *GameObjectFactory::createAcid(Point pos, Point size, Texture* tex){
	GameObject* newWall = new GameObject(pos, size);
	AI* acidAI = new AcidBlockAI(newWall);
	newWall->setTexture(tex);
	newWall->setAI(acidAI);
	newWall->gravityEnabled = false;
	newWall->collidable = true;
	newWall->deletable = true;
	newWall->_magicNumberType = GameObjectTypeBlock;

	_gameObjects.push_back(newWall);
	_aiList.push_back(acidAI);
	return newWall;
}

GameObject *GameObjectFactory::createBullet(GameObject *owner, Point pos, Point size, Texture* tex, Point speed, float damage, float pushForce, bool explosive, float explosionRadius){
	GameObject *newEnemy = new GameObject(pos, size);
	AI* newAi = new BulletAI(owner, newEnemy, damage, speed, pushForce, tex, explosive, explosionRadius);
	newEnemy->setAI(newAi);
	newEnemy->_magicNumberType = GameObjectTypeBullet;
	newEnemy->deletable = true;

	_gameObjects.push_back(newEnemy);
	_aiList.push_back(newAi);
	return newEnemy;
}

GameObject *GameObjectFactory::createBlasterEnemy(Point pos, Point size, float maxSpeed, int health, FireCommandBullet b, std::string animationGroup){
	GameObject *newEnemy = new GameObject(pos, size);
	AI* newAi = new BlasterEnemyAI(newEnemy, maxSpeed, animationGroup);
	newEnemy->setAI(newAi);
	newEnemy->getHealth() = health;
	newEnemy->setMaxHealth(health);
	newEnemy->_magicNumberType = GameObjectTypeEnemy;
	newEnemy->deletable = true;

	BlasterEnemyAI* ai = (BlasterEnemyAI*)newAi;
	ai->setBullet(b); // TODO: Make different variants for "aggression modes"

	_gameObjects.push_back(newEnemy);
	_aiList.push_back(newAi);
	return newEnemy;
}

GameObject *GameObjectFactory::createMGBlasterEnemy(Point pos, Point size, float maxSpeed, int health, FireCommandBullet b, std::string animationGroup){
	GameObject *newEnemy = new GameObject(pos, size);
	AI* newAi = new MachineBlasterEnemyAI(newEnemy, maxSpeed, animationGroup);
	newEnemy->setAI(newAi);
	newEnemy->getHealth() = health;
	newEnemy->setMaxHealth(health);
	newEnemy->_magicNumberType = GameObjectTypeEnemy;
	newEnemy->deletable = true;

	MachineBlasterEnemyAI* ai = (MachineBlasterEnemyAI*)newAi;
	ai->setBullet(b); // TODO: Make different variants for "aggression modes"

	_gameObjects.push_back(newEnemy);
	_aiList.push_back(newAi);
	return newEnemy;
}

GameObject *GameObjectFactory::createBasicEnemy(Point pos, Point size, float maxSpeed, int health, float dmg, std::string animationGroup){
	GameObject *newEnemy = new GameObject(pos, size);
	AI* newAi = new BasicEnemyAI(newEnemy, maxSpeed, dmg, animationGroup);
	newEnemy->setAI(newAi);
	newEnemy->getHealth() = health;
	newEnemy->setMaxHealth(health);
	newEnemy->_magicNumberType = GameObjectTypeEnemy;
	newEnemy->deletable = true;

	_gameObjects.push_back(newEnemy);
	_aiList.push_back(newAi);
	return newEnemy;
}

GameObject *GameObjectFactory::createProp(Point pos, Point size, Texture* tex, bool gravity, bool collidable){
	GameObject *newProp = new GameObject(pos, size);
	AI* newAi = nullptr;
	if(gravity){
		// this ai automatically incorporates gravity
		newAi = new EntityMovingBaseAI(newProp);
	}else{
		newAi = new AI(nullptr);
	}
	newProp->setAI(newAi);
	newProp->getHealth() = 9999;
	newProp->setTexture(tex);
	newProp->collidable = collidable;
	newProp->deletable = true;
	newProp->_magicNumberType = GameObjectTypeProp;

	_gameObjects.push_back(newProp);
	_aiList.push_back(newAi);
	return newProp;
}

GameObject *GameObjectFactory::createAnimationProp(Point pos, Point size, std::string animationGroupName, float speed, int loops){
	GameObject *newProp = new GameObject(pos, size);
	AI* newAi = nullptr;
	newAi = new AnimatedPropAI(newProp, animationGroupName, loops, speed);
	newProp->setAI(newAi);
	newProp->getHealth() = 9999;
	newProp->collidable = false;
	newProp->deletable = true;
	newProp->_magicNumberType = GameObjectTypeProp;

	_gameObjects.push_back(newProp);
	_aiList.push_back(newAi);
	return newProp;
}

GameObject *GameObjectFactory::createSpawner(Point pos, int maxEntities, float spawnDelay, SpawnList& spawnList){
	GameObject *newSpawner = new GameObject(pos, Point{32, 32});
	AI* newAi = nullptr;
	newAi = new SpawnerAI(newSpawner, maxEntities, spawnDelay);
	SpawnerAI* cast = (SpawnerAI*)newAi;
	cast->getSpawnList() = spawnList;
	newSpawner->setAI(newAi);
	newSpawner->getHealth() = 9999;
	newSpawner->collidable = false;
	newSpawner->deletable = true;
	newSpawner->drawable = false;
	newSpawner->_magicNumberType = GameObjectTypeSpawner;

	_gameObjects.push_back(newSpawner);
	_aiList.push_back(newAi);
	return newSpawner;
}

GameObject *GameObjectFactory::createExplosion(Point pos, float radius, float damage, std::string animationGroup){
	GameObject* newExplosion = new GameObject(pos, Point{ radius, radius });
	AI* newAI = new ExplosionAI(newExplosion, radius, damage, animationGroup);
	newExplosion->setAI(newAI);
	newExplosion->setHealth(10000);
	newExplosion->collidable = false;
	newExplosion->drawable = false;
	newExplosion->deletable = true;
	newExplosion->_magicNumberType = GameObjectTypeProp;

	_gameObjects.push_back(newExplosion);
	_aiList.push_back(newAI);
	return newExplosion;
}

/*
struct FireCommandBullet{
	std::string name;
	Texture* tex;
	Point size;
	Point speed;
	float damage;
	float pushPower;
	bool explosive;
	float explosiveRange;
	int cost; // for player to purchase
};
*/

FireCommandBullet GameObjectFactory::generateRubberBullet(int forWho){
	if (forWho == GameObjectTypePlayer){
		return FireCommandBullet{
			"Rubber Bullet",
			TextureManager::instance()->getTexture("tex/ammo/rubber_ball.png"),
			Point{ 15, 15 },
			Point{ 270, 5 },
			15,
			35,
			false, // Temporarilyu explosive for testing.
			0,
			75
		};
	}
	else{
		return FireCommandBullet{
			"Rubber Bullet (ENEMY)",
			TextureManager::instance()->getTexture("tex/ammo/rubber_ball.png"),
			Point{ 15, 15 },
			Point{ 275, 5 },
			19,
			35,
			false,
			0,
			75
		};
	}
}

FireCommandBullet GameObjectFactory::generateLeadBullet(int forWho){
	if (forWho == GameObjectTypePlayer){
		return FireCommandBullet{
			"Lead Bullet",
			TextureManager::instance()->getTexture("tex/ammo/lead_ball.png"),
			Point{ 15, 15 },
			Point{ 420, 5 },
			45,
			15,
			false,
			0,
			150
		};
	}
	else{
			return FireCommandBullet{
				"Lead Bullet",
				TextureManager::instance()->getTexture("tex/ammo/lead_ball.png"),
				Point{ 15, 15 },
				Point{ 420, 5 },
				40,
				15,
				false,
				0,
				150
			};
	}
}

FireCommandBullet GameObjectFactory::generateSilverBullet(int forWho){
	if (forWho == GameObjectTypePlayer){
		return FireCommandBullet{
			"Silver Bullet",
			TextureManager::instance()->getTexture("tex/ammo/silver_bullet.png"),
			Point{ 25, 25 },
			Point{ 630, 5 },
			60,
			20,
			false,
			0,
			350
		};
	}
	else{
		return FireCommandBullet{
			"Silver Bullet",
			TextureManager::instance()->getTexture("tex/ammo/silver_bullet.png"),
			Point{ 25, 25 },
			Point{ 630, 5 },
			60,
			20,
			false,
			0,
			350
		};
	}
}

FireCommandBullet GameObjectFactory::generateRocketBullet(int forWho){
	return FireCommandBullet{
		"Rocket",
		TextureManager::instance()->getTexture("tex/ammo/rocket.png"),
		Point{ 35, 20 },
		Point{ 830, 5 },
		150,
		20,
		true,
		125,
		500
	};
}

FireCommandBullet GameObjectFactory::generateGoldBullet(int forWho){
	if (forWho == GameObjectTypePlayer){
		return FireCommandBullet{
			"Gold Bullet",
			TextureManager::instance()->getTexture("tex/ammo/gold_bullet.png"),
			Point{ 25, 25 },
			Point{ 630, 5 },
			85,
			20,
			false,
			0,
			500
		};
	}
	else{
		return FireCommandBullet{
			"Gold Bullet(ENE)",
			TextureManager::instance()->getTexture("tex/ammo/gold_bullet.png"),
			Point{ 25, 25 },
			Point{ 630, 5 },
			100,
			20,
			false,
			0,
			350
		};
	}
}

FireCommandBullet GameObjectFactory::generateMGBullet(int forWho){
		return FireCommandBullet{
			"Gold Bullet",
			TextureManager::instance()->getTexture("tex/ammo/gold_bullet.png"),
			Point{ 25, 25 },
			Point{ 700, 5 },
			15,
			20,
			false,
			0,
			500
		};
}