#ifndef JUMP_COMMAND_H
#define JUMP_COMMAND_H

#include "Command.h"

class JumpCommand : public Command{
	public:
		JumpCommand() : Command(nullptr){}
		JumpCommand(const JumpCommand& other) = default;
		JumpCommand(AI* _aiParent, float height, float maxHeight);
		~JumpCommand();
		
		void reset() { _jumpCount = 0; }
		void update(float dt, World& world);
		
		void setMaxJumps(int max) { _maxJumps = max; }
		int getMaxJumps() { return _maxJumps; }
		int getCurrentlyJumped() { return _jumpCount; }
	private:
		float _height, _maxHeight;
		int _jumpCount = 0, _maxJumps;

		// for now no animation but in the future
		// add one
};

#endif
