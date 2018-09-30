#include "AcidicBlockAI.h"
#include "GameObject.h"
#include "SoundManager.h"

void AcidBlockAI::kill(GameObject* operate){
	GameObject* parent = AI::getParent();
	if (operate != parent)
		// whatever's inside is going to die.
		if (operate->getType() != GameObjectTypeProp && operate->getType() != GameObjectTypeBullet && operate->getType() != GameObjectTypeSpawner && operate->getType() != GameObjectTypeBlock){
			operate->getHealth() = -1;
			SoundManager::instance()->playSound("audio/fx/death_by_acid.wav", 100, -1);
		}
}

void AcidBlockAI::update(float dt, World& world){
	predictionCollide({ 0, 0 }, world, dt);
	if (_animation.isFinished()){
		_animation.reset();
	}
	AI::getParent()->setTexture(_animation.getCurrentFrame()->getTexture());
	_animation.update(dt, 0.15);
}

bool AcidBlockAI::processCollision(GameObject* operate, World& world, float dt){
	GameObject* parent = AI::getParent();
	if (operate != parent)
		// whatever's inside is going to die.
		if (operate->getType() != GameObjectTypeProp && operate->getType() != GameObjectTypeBullet && operate->getType() != GameObjectTypeSpawner && operate->getType() != GameObjectTypeBlock){
				operate->getHealth() = -1;
				SoundManager::instance()->playSound("audio/fx/death_by_acid.wav", 100, -1);
				return false;
		}
	return true;
}

bool AcidBlockAI::predictionCollide(Point movement, World& world, float dt){
	return true;
}

bool AcidBlockAI::predictionCollideX(float x, World& world, float dt){
	return true;
}

bool AcidBlockAI::predictionCollideY(float y, World& world, float dt){
	return true;
}