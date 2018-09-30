#ifndef FIRE_COMMAND_H
#define FIRE_COMMAND_H

#include "Command.h"
#include "TextureManager.h"

struct FireCommandBullet{
	std::string name;
	Texture* tex;
	Point size;
	Point speed;
	float damage;
	float pushPower;
	bool explosive;
	float explosiveRange;
	int cost; // for player to purchase
};

/*
 * TODO: Add bullet so it can actually do some powerful stuff
 */
class FireCommand : public Command{
	public:
		FireCommand() : Command(nullptr){}
		FireCommand(AI* _aiParent, int fireFrame, std::string animationName);
		FireCommand(const FireCommand& other) = default;
		~FireCommand();

		void update(float dt, World& world);
		void reset(){ _animation.reset(); _fired = false; getParent()->getParent()->getVelocity().x = 0; }

		void setDirection(int direction) { _direction = direction; }
		void setFireSpeed(float fireSpeed) { _fireSpeed = fireSpeed; }

		bool isFinished() { return _animation.isFinished(); }
		void setCurrentBullet(FireCommandBullet b) { _bullet = b; }
	private:
		FireCommandBullet _bullet;
		bool _fired = false;
		float _fireSpeed = 0;

		Animation _animation;

		int _direction = -1;
		int _fireFrame = 0;
};

#endif
