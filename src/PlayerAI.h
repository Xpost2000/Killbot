#ifndef PLAYER_AI_H
#define PLAYER_AI_H

#include "InputManager.h"
#include "EntityMovingBaseAI.h"

#include "Animation.h"

#include "IdleCommand.h"
#include "MoveCommand.h"
#include "JumpCommand.h"
#include "AttackCommand.h"
#include "FireCommand.h"

// uses the input manager to control the player entity.
/*
 * TODO: Pass in player data struct to get information about
 * 	 player ammo and stuff like that.
 *
 * 	 Mostly ammo and health.
 */
// 1 Rubber
// 2 Lead
// 3 Silver
// 4 Gold
// 5 rockets
const int bullet_types = 5;
class PlayerAI : public EntityMovingBaseAI{
	public:
		PlayerAI(GameObject* parent, InputManager* input, std::string animationGroup = PlayerAnimationGroupName);
		~PlayerAI();

		void ai_update(float dt, World& world);

		int& getBulletIndex() { return current_bullet_index; }
		int& getBulletCountForCurrentIndex() { return bullet_count[getBulletIndex()]; }

		int& getBulletCountForIndex(int index) { return bullet_count[index]; }

		void reset(){ 
			bullet_count[0] = 45;
			bullet_count[1] = 40;
			bullet_count[2] = 10;
			bullet_count[3] = 8;
			bullet_count[4] = 2;
			current_bullet_index = 0; 
		}
	private:
		// bullet counts
		int bullet_count[bullet_types];
		int current_bullet_index = 0; // always start with rubber.
		// ok I'll admit my code is starting to fall apart over here.

		bool allowControl = true;

		AttackCommand attackCommand;
		IdleCommand idleCommand;
		MoveCommand moveCommand;
		JumpCommand jumpCommand;
		FireCommand fireCommand;

		InputManager* _input;
};

#endif
