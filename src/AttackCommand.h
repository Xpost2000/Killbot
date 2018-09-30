#ifndef ATTACK_COMMAND_H
#define ATTACK_COMMAND_H

#include "Command.h"
#include "TextureManager.h"

/*
 * This is strictly a melee class.
 */
class AttackCommand : public Command{
	public:
		AttackCommand() : Command(nullptr){}
		AttackCommand(AI* _aiParent, int fireFrame, std::string animationName);
		~AttackCommand();

		void update(float dt, World& world);
		void reset(){ _animation.reset(); _attack = false; }

		void setDirection(int direction) { _direction = direction; }
		void setAttackSpeed(float fireSpeed) { _attackSpeed = fireSpeed; }
		void setDamage(float dmg) { _damage = dmg; }
		void setRadiusX(float radius) { _radiusOfHitX = radius; }
		void setRadiusY(float radius) { _radiusOfHitY = radius; }
		bool isFinished() { return _animation.isFinished(); }
	private:
		bool _corpseSpawned = false;
		float _radiusOfHitX = 0, _radiusOfHitY;
		float _damage = 0;

		bool _attack = false;
		float _attackSpeed = 0;

		Animation _animation;

		int _direction = -1;
		int _attackFrame = 0;
};

#endif
