#include "EndGameState.h"
#include "SoundManager.h"
#include "CefManager.h"

EndGameState::EndGameState(InputManager* input){

}

EndGameState::~EndGameState(){

}

void EndGameState::init(){

}

void EndGameState::update(float dt){
	if (!SoundManager::instance()->isMusicPlaying())
		SoundManager::instance()->playMusic("audio/music/end_music.ogg", 100, -1);
}

void EndGameState::draw(Renderer2D* renderer){
	renderer->RenderRectangle(CefManager::instance()->GetRenderHandler()->getTexture(), Point{ 0, 0 }, Point{ renderer->getWidth(), renderer->getHeight() }, UV{ 0, 0, 1, 1 }, Color{ 255, 255, 255, 255 });
}

bool EndGameState::OnEnter(){
	SoundManager::instance()->haltMusic();
	CefManager::instance()->GetCefBrowser()->GetMainFrame()->LoadURL(std::string("file://" + std::string(SDL_GetBasePath()) + "htmlui/endGame.html"));
	return true;
}

bool EndGameState::OnExit(){
	SoundManager::instance()->haltMusic();
	return true;
}