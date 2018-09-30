#ifndef LOADINGSCREEN_STATE_H
#define LOADINGSCREEN_STATE_H

#include "State.h"

class LoadingScreenState : public State{
	public:
		LoadingScreenState();
		~LoadingScreenState();
		bool OnEnter();
		bool OnExit();
		void update(float dt);
		void draw(Renderer2D* renderer);
	private:
		bool _drawScreenAlready=false;
};

#endif
