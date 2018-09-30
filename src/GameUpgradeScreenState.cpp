#include "GameUpgradeScreenState.h"
#include "StateMachine.h"
#include "GameState.h"
#include "constants.h"
#include "SoundManager.h"
#include "CefManager.h"

GameUpgradeScreenState::GameUpgradeScreenState(InputManager* input) : _input(input){
}

GameUpgradeScreenState::~GameUpgradeScreenState(){
}

void GameUpgradeScreenState::init(){
}

bool GameUpgradeScreenState::OnEnter(){
	SoundManager::instance()->haltMusic();
	SoundManager::instance()->playMusic("audio/music/upgrade_music.ogg", 100, -1);
	CefManager::instance()->GetCefBrowser()->GetMainFrame()->LoadURL(std::string("file://" + std::string(SDL_GetBasePath()) + "htmlui/upgrade.html"));
	return true;
}

bool GameUpgradeScreenState::OnExit(){
	SoundManager::instance()->haltMusic();
	return true;
}

void GameUpgradeScreenState::update(float dt){
	if (!SoundManager::instance()->isMusicPlaying())
		SoundManager::instance()->playMusic("audio/music/upgrade_music.ogg", 100, -1);
	if(_input->isKeyPressed(SDL_SCANCODE_ESCAPE)){
		_parent->setCurrent("mainMenu");	
	}
}

bool GameUpgradeScreenState::SetupGame(int whatMode){
	switch (whatMode){
	case GameModeBossGauntlet:
		if (canFightBoss){
			GameState* ptr = (GameState*)(_parent->getState("game"));
			ptr->_gameMode = GameModeBossGauntlet;
			ptr->setUpGameMode();
			_parent->setCurrent("game");
			return true;
		}
		break;
	case GameModeStandard:
		GameState* ptr = (GameState*)(_parent->getState("game"));
		ptr->_gameMode = GameModeStandard;
		ptr->setUpGameMode();
		_parent->setCurrent("game");
		return true;
		break;
	}

	return false;
}

void GameUpgradeScreenState::draw(Renderer2D* renderer){
	renderer->RenderRectangle(CefManager::instance()->GetRenderHandler()->getTexture(), Point{ 0, 0 }, Point{ renderer->getWidth(), renderer->getHeight() }, UV{ 0, 0, 1, 1 }, Color{ 255, 255, 255, 255 });
}
