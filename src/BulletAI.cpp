#include "BulletAI.h"
#include "GameObject.h"
#include "constants.h"
#include "GameObjectFactory.h"
#include "SoundManager.h"
#include "TextureManager.h"
#include <iostream>

#include "Engine.h"

BulletAI::BulletAI(GameObject* parentOfBullet, GameObject* parent, int dmg, Point speed, float pushForce, Texture* texture, bool explosive, float explosionRadius) : AI(parent), _damage(dmg), _speedX(speed.x), _speedY(speed.y), _pushForce(pushForce), _explosive(explosive), _explosiveRadius(explosionRadius), _texture(texture), _parentOfBullet(parentOfBullet){
	if(parent && parentOfBullet){
		parent->flipX = parentOfBullet->flipX;
		_direction = parent->flipX ? -1 : 1;
	}
}

BulletAI::~BulletAI(){
}

void BulletAI::update(float dt, World& world){
		GameObject* parent = AI::getParent();
		bool xCollided = predictionCollideX(parent->getVelocity().x, world, dt);
		bool yCollided = predictionCollideX(parent->getVelocity().y, world, dt);

		parent->getVelocity().x = _speedX*dt*_direction;
		parent->getVelocity().y = _speedY*dt;

		if(xCollided)
			parent->getPosition().x += parent->getVelocity().x;
		if(yCollided)
			parent->getPosition().y += parent->getVelocity().y;
  		parent->setTexture(_texture);
		parent->setHitBox(parent->getPosition(), parent->getSize());
}

bool BulletAI::predictionCollide(Point movement, World& world, float dt){
	return predictionCollideX(movement.x, world, dt) && predictionCollideY(movement.y, world, dt);
}

bool BulletAI::predictionCollideX(float x, World& world, float dt){
	GameObject* parent = AI::getParent();
	GameObject predictionClone = *parent;
	predictionClone.getHitBoxPos().x += x;
	for(auto& ent : world.getEntities()){
		if(ent != parent){
			if(predictionClone.collide(*ent)){
				return processCollision(ent, world, dt);
			}	
		}
	}
	return true;
}

bool BulletAI::predictionCollideY(float y, World& world, float dt){
	GameObject* parent = AI::getParent();
	GameObject predictionClone = *parent;
	predictionClone.getHitBoxPos().y += y;
	for(auto& ent : world.getEntities()){
		if(ent != parent){
			if(predictionClone.collide(*ent)){
				return processCollision(ent, world, dt);
			}	
		}
	}
	return true;
}

bool BulletAI::processCollision(GameObject* ent, World& world, float dt){
	GameObject* parent = AI::getParent();
	if(ent != _parentOfBullet)
	if(ent->getType() != GameObjectTypeProp && ent->getType() != GameObjectTypeBullet && ent->getType() != GameObjectTypeSpawner){
		if (_explosive){
			world.AddEntity(GameObjectFactory::instance()->createExplosion(Point{ parent->getPosition().x , parent->getPosition().y}, _explosiveRadius, _damage, ExplosionAnimationGroupName));
		}
		if(ent->getType() == GameObjectTypeBlock){
			parent->getHealth() = -1;
			SoundManager::instance()->playSound("audio/fx/hit.wav", 100, -1);
			Engine::instance()->getRenderer()->ScreenShake(0.15, 1.35, 1.35);
			return false;
		}else{
			if (parent->getHealth() > 0){
				if (!_explosive)
				ent->getHealth() -= _damage;
				ent->flash();
			}
			parent->getHealth() = -1;
			SoundManager::instance()->playSound("audio/fx/hit.wav", 100, -1);
			Engine::instance()->getRenderer()->ScreenShake(0.15, 1.35, 1.35);
			if(ent->getHealth() <= 0){
				// make a corpse for it.
				// also admittidly the bullet shouldn't be responsible
				// for making a corpse for a dead enemy.
				// Oh well. Just pray this destructive path doesn't break anything else.
				// TODO make this part more flexible
				if(!_corpseSpawned){
					GameObject* corpseObject = GameObjectFactory::instance()->createProp(ent->getPosition(), Point{ ent->getSize().x - 3, ent->getSize().y - 15 }, TextureManager::instance()->getTexture("tex/killbot_corpse.png"), true, false);
					corpseObject->flipX = ent->flipX;
					world.AddEntity(corpseObject);
					printf("Enemy corpse spawned;\n");
					_corpseSpawned = true;
				}
			}
			//Reimplement later on.
			ent->getVelocity().x = _pushForce*_direction;
			return false;
		}
	}
	return true;
}
