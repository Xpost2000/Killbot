#ifndef MGBLASTERENEMY_AI_H
#define MGBLASTERENEMY_AI_H

#include "EntityMovingBaseAI.h"

#include "Animation.h"

#include "IdleCommand.h"
#include "MoveCommand.h"
#include "JumpCommand.h"
#include "FireCommand.h"

#include "RandomNumberGenerator.h"

/*
 *
 * Just as dangerous as the normal blaster * 1.4 due to burst firing rapid little bullets.
 */

class MachineBlasterEnemyAI : public EntityMovingBaseAI{
	public:
		MachineBlasterEnemyAI(GameObject* parent, float maxSpeed, std::string animationGroup = BlasterEnemyAnimationGroupName);
		~MachineBlasterEnemyAI();

		void setBullet(FireCommandBullet bl){ _bullet = bl; }
		void ai_update(float dt, World& world);
	private:
		FireCommandBullet _bullet;

		float _commandDelay = 0, _jumpDelay = 0;
		int _mgTimesFired = 0;
		const int   _mgFireTimeMax = 6; // amount of times to fire in a burst. Hard code to be 6.
		bool _flip=false;

		IdleCommand idleCommand;
		MoveCommand moveCommand;
		FireCommand fireCommand;
		JumpCommand jumpCommand;
};

#endif
