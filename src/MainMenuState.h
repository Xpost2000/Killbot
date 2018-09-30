#ifndef MAINMENU_STATE_H
#include "State.h"
#include "InputManager.h"

class MainMenuState : public State{
	public:
		MainMenuState(InputManager* input);
		~MainMenuState();
		void init();
		bool OnEnter();
		bool OnExit();
		void update(float dt);
		void draw(Renderer2D* renderer);
	private:
		InputManager* _input;
};

#endif
