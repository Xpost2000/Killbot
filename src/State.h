#ifndef STATE_H
#define STATE_H
#include "Renderer2D.h"

class StateMachine;
class State{
	public:
		State();
		~State();
		virtual void init(){}
		virtual bool OnEnter() { return true; }
		virtual bool OnExit() { return true; }
		virtual void update(float dt) = 0;
		virtual void draw(Renderer2D* renderer) = 0;
	protected:
		friend class StateMachine;
		StateMachine* _parent;
};

class NullState : public State{
	public:
		NullState() : State(){}
		~NullState() {}
		void update(float dt){}
		void draw(Renderer2D* renderer){}
};

#endif
