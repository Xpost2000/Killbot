#ifndef GAMEUPGRADE_STATE_H
#define GAMEUPGRADE_STATE_H
#include "State.h"
#include "InputManager.h"

class GameUpgradeScreenState : public State{
	public:
		GameUpgradeScreenState(InputManager* input);
		~GameUpgradeScreenState();
		void init();
		bool OnEnter();
		bool OnExit();
		void update(float dt);
		void draw(Renderer2D* renderer);

		bool SetupGame(int whatMode);
		
		void ForceBossFight(){ canFightBoss = true; }

		bool CanFightBoss() { return canFightBoss; }
	private:
		friend class GameState;
		bool canFightBoss = false; // just demo.

		InputManager* _input;
};

#endif
