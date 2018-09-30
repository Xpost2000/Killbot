#ifndef GAMEOVER_STATE_H
#define GAMEOVER_STATE_H

#include "State.h"
#include "InputManager.h"

class GameOverState : public State{
	public:
		GameOverState(InputManager* input);
		~GameOverState();

		void init();

		void update(float dt);
		void draw(Renderer2D* renderer);

		bool OnEnter();
		bool OnExit();
	private:
		InputManager* _input = nullptr;
};

#endif