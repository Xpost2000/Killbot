#ifndef END_GAME_STATE_H
#define END_GAME_STATE_H
#include "State.h"
#include "InputManager.h"

class EndGameState : public State{
	public:
		EndGameState(InputManager* input);
		~EndGameState();

		void init();

		void update(float dt);
		void draw(Renderer2D* renderer);

		bool OnEnter();
		bool OnExit();
	private:
		InputManager* _input = nullptr;
};

#endif