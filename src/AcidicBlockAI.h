#ifndef ACIDIC_BLOCK_H
#define ACIDIC_BLOCK_H
#include "AnimationManager.h"
#include "AI.h"
/*
	somehow a block has the concept of intelligence. It's really supposed to fry whatever falls into it though.
*/
class AcidBlockAI : public AI{
public:
	AcidBlockAI(GameObject* parent) : AI(parent){ _animation = *AnimationManager::instance()->getGroup("acid")->getAnimation("animation"); }
	AcidBlockAI::~AcidBlockAI(){}
	void update(float dt, World& world);
	void kill(GameObject* operate);
private:
	bool processCollision(GameObject* operate, World& world, float dt);
	bool predictionCollide(Point movement, World& world, float dt);
	bool predictionCollideX(float x, World& world, float dt);
	bool predictionCollideY(float y, World& world, float dt);

	Animation _animation;
};

#endif