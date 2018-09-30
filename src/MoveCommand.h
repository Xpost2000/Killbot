#ifndef MOVE_COMMAND_H
#define MOVE_COMMAND_H

#include "Command.h"

class MoveCommand : public Command{
	public:
		MoveCommand() : Command(nullptr){}
		MoveCommand(const MoveCommand& other) = default;
		MoveCommand(AI* _aiParent, float maxSpeed, std::string animationName);
		~MoveCommand();
		
		void setDirection(int direction) { _direction = direction; }
		void reset() { _animation.reset(); }
		void update(float dt, World& world);

	private:
		bool _playedSound=false;

		Animation _animation;

		int _direction = -1;
		float _maxSpeed;
};

#endif
