#ifndef CREDITS_STATE_H
#define CREDITS_STATE_H
#include "State.h"
#include "InputManager.h"

class CreditsState : public State{
	public:
		CreditsState(InputManager* input);
		~CreditsState();

		void init();

		void update(float dt);
		void draw(Renderer2D* renderer);

		bool OnEnter();
		bool OnExit();
	private:
		InputManager* _input = nullptr;
};

#endif