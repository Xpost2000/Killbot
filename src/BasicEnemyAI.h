#ifndef BASICENEMY_AI_H
#define BASICENEMY_AI_H

#include "EntityMovingBaseAI.h"

#include "Animation.h"

#include "IdleCommand.h"
#include "MoveCommand.h"
#include "JumpCommand.h"

#include "AttackCommand.h"

/*
 * This enemy basically just
 * charges in a direction.
 *
 * Very stupid.
 * Doesn't even try to get to the player.
 * Just walks around like a mindless zombie
 *
 * This is a test AI used for testing
 * game mechanics and stuff.
 *
 * The actual basic AI is probably a bit more complex
 */

class BasicEnemyAI : public EntityMovingBaseAI{
	public:
		BasicEnemyAI(GameObject* parent, float maxSpeed, float dmg, std::string animationGroup = BasicEnemyAnimationGroupName);
		~BasicEnemyAI();

		void ai_update(float dt, World& world);
	private:
		bool _flip=false;
		float _commandDelay = 0, _jumpDelay = 0;

		IdleCommand idleCommand;
		MoveCommand moveCommand;
		JumpCommand jumpCommand;
		AttackCommand attackCommand;
};

#endif
