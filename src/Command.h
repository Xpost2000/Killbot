#ifndef COMMAND_H
#define COMMAND_H

#include "GameObject.h"
#include "World.h"
class AI;

class Command{
	public:
		// TODO Use Identification of Parent.
		Command(AI* _aiParent);
		~Command();
		
		virtual void reset() = 0;
		virtual void update(float dt, World& world) = 0;
	protected:
		AI* getParent(){ return _parent; }
	private:
		AI* _parent;
};

#endif
