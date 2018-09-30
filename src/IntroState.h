#ifndef INTRO_STATE_H
#define INTRO_STATE_H

#include "State.h"
#include "InputManager.h"
#include "AnimationManager.h"

class IntroState : public State{
	public:
		IntroState(InputManager* input);
		~IntroState();
		void init();

		void update(float dt);
		void draw(Renderer2D* renderer);

		bool OnEnter();
		bool OnExit();
	private:
		float _alphaForText = -150;
		float _endPadding = 4.25; // I'm aware there's an issue in the animation system. So this is my fix for it :|
		Animation* _introAnimation = nullptr;
		InputManager *_input = nullptr;
};

#endif