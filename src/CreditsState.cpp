#include "CreditsState.h"
#include "SoundManager.h"
#include "CefManager.h"

CreditsState::CreditsState(InputManager* input){

}

CreditsState::~CreditsState(){

}

void CreditsState::init(){}

void CreditsState::update(float dt){
	if (!SoundManager::instance()->isMusicPlaying())
		SoundManager::instance()->playMusic("audio/music/credits_music.ogg", 100, -1);
}

void CreditsState::draw(Renderer2D* renderer){
	renderer->RenderRectangle(CefManager::instance()->GetRenderHandler()->getTexture(), Point{ 0, 0 }, Point{ renderer->getWidth(), renderer->getHeight() }, UV{ 0, 0, 1, 1 }, Color{ 255, 255, 255, 255 });
}

bool CreditsState::OnEnter(){
	SoundManager::instance()->haltMusic();
	CefManager::instance()->GetCefBrowser()->GetMainFrame()->LoadURL(std::string("file://" + std::string(SDL_GetBasePath()) + "htmlui/credits.html"));
	return true;
}

bool CreditsState::OnExit(){
	SoundManager::instance()->haltMusic();
	return true;
}