#include "MainMenuState.h"
#include "StateMachine.h"
#include "SoundManager.h"
#include "CefManager.h"

MainMenuState::MainMenuState(InputManager* input) : _input(input){
}

MainMenuState::~MainMenuState(){
}

void MainMenuState::init(){
}

bool MainMenuState::OnEnter(){
	CefManager::instance()->GetCefBrowser()->GetMainFrame()->LoadURL(std::string("file://" + std::string(SDL_GetBasePath()) + "htmlui/mainmenu.html"));
	SoundManager::instance()->haltMusic();
	return true;
}

bool MainMenuState::OnExit(){
	SoundManager::instance()->haltMusic();
	return true;
}

void MainMenuState::update(float dt){
	if (!SoundManager::instance()->isMusicPlaying())
		SoundManager::instance()->playMusic("audio/music/main_menu_music.ogg", 100, -1);
}

void MainMenuState::draw(Renderer2D* renderer){
	// Render the HTML HUD
	renderer->RenderRectangle(CefManager::instance()->GetRenderHandler()->getTexture(), Point{ 0, 0 }, Point{ renderer->getWidth(), renderer->getHeight() }, UV{0, 0, 1, 1}, Color{ 255, 255, 255, 255 });
}
