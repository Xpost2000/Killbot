#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include <string>
#include <map>
#include "Renderer2D.h"

class State;
class StateMachine{
	public:
		StateMachine();
		~StateMachine();

		State* addState( std::string name, State* ptr );
		State* getState( std::string name ) { return _states[name]; }
		State* getCurrent() { return _current; }

		void setCurrent(std::string name);

		void update(float dt);
		void draw(Renderer2D* renderer);
	private:
		State* _current = nullptr;
		std::map<std::string, State*> _states;
};

#endif
