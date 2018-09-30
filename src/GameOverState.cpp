#include "GameOverState.h"
#include "StateMachine.h"
#include "constants.h"

#include "SoundManager.h"
#include "CefManager.h"

#include "GameState.h"

GameOverState::GameOverState(InputManager* input) : _input(input){

}

GameOverState::~GameOverState(){

}

void GameOverState::init(){

}

void GameOverState::update(float dt){
	SoundManager::instance()->haltMusic();
}

void GameOverState::draw(Renderer2D* renderer){
	renderer->RenderRectangle(CefManager::instance()->GetRenderHandler()->getTexture(), Point{ 0, 0 }, Point{ renderer->getWidth(), renderer->getHeight() }, UV{ 0, 0, 1, 1 }, Color{ 255, 255, 255, 255 });
}

bool GameOverState::OnEnter(){
	SoundManager::instance()->haltMusic();
	CefManager::instance()->GetCefBrowser()->GetMainFrame()->LoadURL(std::string("file://" + std::string(SDL_GetBasePath()) + "htmlui/gameOver.html"));
	return true;
}

bool GameOverState::OnExit(){
	GameState* ptr = (GameState*)_parent->getState("game");
	ptr->gameOverReset();
	return true;
}