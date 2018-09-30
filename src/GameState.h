#ifndef  GAMESTATE_H
#define GAMESTATE_H

#include "State.h"
#include "World.h"

#include "GameObject.h"

#include "PlayerAI.h"

class GameState : public State{
	public:
		GameState(InputManager* input);
		~GameState();
		void init();
		bool OnEnter();
		bool OnExit();
		void update(float dt);
		void draw(Renderer2D* renderer);

		void setUpGameMode();
		void parseMap(int map[24][32]);

		void gameOverReset();

		GameObject* getPlayer() { return player; }
		GameObject* getCurrentBoss() { return _currentBoss; }

		int getCurrentRound() { return _gameRound; }

		int& getGameScore() { return _gameScore; }
		int& getGameMode() { return _gameMode; }
		// this is static because I need global access for this...
		// admittidly using messaging systems would've been effective but I don't know
		// if I can restructure the code to work with it.
		static std::string &getMessage(){ return _msg; }
		int getPlayerLives() { return _playerLives; }
		void reset();
	private:
		GameObject* _currentBoss = nullptr;
		//TODO:
		//
		//Work with this stuff.
		//
		friend class GameUpgradeScreenState;
		static std::string _msg;
		int _gameMode = 0;
		// TODO make more flexible boss fights
		int _currentBossOnRoster = 0;

		int _gameRound = 1;
		float _gameRoundWaitTime = 5; // in seconds
		float _gameWaitTilBackToMenu = 5; // again in seconds
		
		int _gameScore = 0;

		bool _roundComplete = false;

		int _playerLives = 3; // 3 lives non purchasable.

		InputManager* _input = nullptr;
		World world;

		GameObject *player = nullptr;//(Point {0, 384+50}, Point{30, 50});
};

#endif
