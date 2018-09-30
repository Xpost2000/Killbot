#ifndef ENTITYMOVINGBASEAI_H
#define ENTITYMOVINGBASEAI_H

/*
 * Basically anything but the bullet
 * follows this.
 * 
 * It's the same as the base AI class
 * but it handles physics automatically for it's bretheren.
 * 
 * this is a seperate class to avoid code retyping.
 *
 * also handles commands automatically.
*/

#include "AI.h"
#include "Command.h"

class EntityMovingBaseAI : public AI{
	public:
		EntityMovingBaseAI(GameObject* parent);
		~EntityMovingBaseAI();
		void update(float dt, World& world) final;
	protected:
		bool predictionCollide(Point movement, World& world);
		bool predictionCollideX(float x, World& world);
		bool predictionCollideY(float y, World& world);

		bool xCollided = false; // for AI Purposes

		bool _onGround = false;

		Command* _currentCommand = nullptr;

		virtual void ai_update(float dt, World& world){}
};


#endif
