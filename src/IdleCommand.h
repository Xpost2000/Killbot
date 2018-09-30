#ifndef IDLE_COMMAND_H
#define IDLE_COMMAND_H

#include "Command.h"

// just cycle through an idle animation
class IdleCommand : public Command{
	public:
		IdleCommand() : Command(nullptr){}
		IdleCommand(const IdleCommand& other) = default;
		IdleCommand(AI* _aiParent, float animationSpeed, std::string animationName);
		~IdleCommand();

		void update(float dt, World& world);
		void reset() { _animation.reset(); }
	private:
		Animation _animation;
		float _animationSpeed;
};

#endif
