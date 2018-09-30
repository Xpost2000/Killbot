#ifndef EXPLOSION_AI_H
#define EXPLOSION_AI_H

#include "AnimationManager.h"
#include "AI.h"

/*
Create an explosion and disappear.

It's really "blast" damage
*/

class ExplosionAI : public AI{
	public:
		ExplosionAI(GameObject* parent, float radius, float damage, std::string animationGroup);
		~ExplosionAI();
		void update(float dt, World& world);
	private:
		Animation* _animation;
		float _radius;
		float _damage;
		bool _hurtAlready = false;
};

#endif