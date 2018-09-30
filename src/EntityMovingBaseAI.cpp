#include "EntityMovingBaseAI.h"
#include "SoundManager.h"
#include "constants.h"
#include "AcidicBlockAI.h"

#include <algorithm>

EntityMovingBaseAI::EntityMovingBaseAI(GameObject* parent) : AI(parent){
}

EntityMovingBaseAI::~EntityMovingBaseAI(){
}
void EntityMovingBaseAI::update(float dt, World& world){
	GameObject* parent = AI::getParent();
	if(parent->getType() == GameObjectTypeProp){
		parent->setHitBox(parent->getPosition(), parent->getSize());
	}
	if(parent->getHealth() > 0){
		if (!_onGround)
		if (parent->getVelocity().x < 0){
			parent->getVelocity().x += GravityStrength*dt;
			parent->getVelocity().x = std::min<float>(parent->getVelocity().x, 0);
		}
		else{
			parent->getVelocity().x -= GravityStrength*dt;
			parent->getVelocity().x = std::max<float>(parent->getVelocity().x, 0);
		}

		ai_update(dt, world);

		xCollided = predictionCollideX(parent->getVelocity().x*dt, world);

		parent->getVelocity().y += GravityStrength*dt;
		parent->getVelocity().y = std::min<float>(parent->getVelocity().y, GravityLimit);

		bool collideY = predictionCollideY((parent->getVelocity().y)*dt, world);
		
		if (collideY){
			_onGround = false;
		}

		if (xCollided)
		parent->getPosition().x += parent->getVelocity().x*dt;
		parent->getPosition().y += parent->getVelocity().y*dt;

		if(_currentCommand)
			_currentCommand->update(dt, world);
	}
}

bool EntityMovingBaseAI::predictionCollide(Point movement, World& world){
	return predictionCollideX(movement.x, world) && predictionCollideY(movement.y, world);
}

bool EntityMovingBaseAI::predictionCollideX(float x, World& world){
	GameObject* parent = AI::getParent();
	GameObject predictionClone = *parent;
	predictionClone.getHitBoxPos().x += x;
	for(auto& ent : world.getEntities()){
		if(ent != parent){
			if(predictionClone.collide(*ent) && ent->collidable){
				parent->getVelocity().x = 0;
				// this is acid.
				if (ent->getType() == GameObjectTypeBlock && ent->getAI() != nullptr){
					AcidBlockAI* ai = (AcidBlockAI*)ent->getAI();
					ai->kill(parent);
				}
				if (parent->getPosition().y > ent->getPosition().y){
					_onGround = false;
				}
				else{
					_onGround = true;
				}
				return false;
			}	
		}
	}
	return true;
}

bool EntityMovingBaseAI::predictionCollideY(float y, World& world){
	GameObject* parent = AI::getParent();
	GameObject predictionClone = *parent;
	predictionClone.getHitBoxPos().y += y;
//	_wasAbove = false;
	for(auto& ent : world.getEntities()){
		if(ent != parent){
			if(predictionClone.collide(*ent) && ent->collidable){
				parent->getVelocity().y = 0;
				if (ent->getType() == GameObjectTypeBlock && ent->getAI() != nullptr){
					AcidBlockAI* ai = (AcidBlockAI*)ent->getAI();
					ai->kill(parent);
				}

				if (parent->getPosition().y > ent->getPosition().y){
					_onGround = false;
				}
				else{
					_onGround = true;
				}
				return false;
			}	
		}
	}
	return true;
}
