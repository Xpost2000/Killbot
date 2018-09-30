#ifndef BLASTERENEMY_AI_H
#define BLASTERENEMY_AI_H

#include "EntityMovingBaseAI.h"

#include "Animation.h"

#include "IdleCommand.h"
#include "MoveCommand.h"
#include "JumpCommand.h"
#include "FireCommand.h"

#include "RandomNumberGenerator.h"

/*
 * This is the shooting enemy. "Blaster"
 *
 * Basically as dumb as the BasicEnemyAI
 * but this one can shoot back!
 */

class BlasterEnemyAI : public EntityMovingBaseAI{
	public:
		BlasterEnemyAI(GameObject* parent, float maxSpeed, std::string animationGroup = BlasterEnemyAnimationGroupName);
		~BlasterEnemyAI();

		void setBullet(FireCommandBullet bl){ _bullet = bl; }
		void ai_update(float dt, World& world);
	private:
		FireCommandBullet _bullet;

		float _commandDelay = 0, _jumpDelay = 0;
		bool _flip=false;

		IdleCommand idleCommand;
		MoveCommand moveCommand;
		FireCommand fireCommand;
		JumpCommand jumpCommand;
};

#endif
