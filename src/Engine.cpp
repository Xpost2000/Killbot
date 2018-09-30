#include "Engine.h"
#include <iostream>
#include "include\cef_app.h"

Engine* Engine::_instance = nullptr;

Engine::Engine(std::string name, int w, int h, bool fullscreen){
	_basePath = SDL_GetBasePath();

	AnimationManager::instance();
	TextureManager::instance(); // just to instanciate it.
	SoundManager::instance();

	SoundManager::instance()->addSound("audio/fx/fire_cannon.wav");

	_display.init(name, w, h, fullscreen);
	_renderer.init(w, h);
	_renderer.AddFont("fonts/OCRAEXT.TTF", "ocr");

	// Init CEF Based Stuff here
	CefManager::instance()->InitBrowser(1024, 768, "about:blank");
	// End of My CEF Stuff

	_stateMachine.addState("load", new LoadingScreenState());
	_stateMachine.addState("upgradeScreen", new GameUpgradeScreenState(&_input));
	_stateMachine.addState("mainMenu", new MainMenuState(&_input));
	_stateMachine.addState("game", new GameState(&_input));
	_stateMachine.addState("intro", new IntroState(&_input));
	_stateMachine.addState("gameOver", new GameOverState(&_input));
	_stateMachine.addState("credits", new CreditsState(&_input));
	_stateMachine.addState("endGame", new EndGameState(&_input));

	_stateMachine.addState("quit", new NullState());

	_stateMachine.setCurrent("load");
}

Engine::~Engine(){
	CefManager::instance()->ShutdownBrowser();

	delete AnimationManager::instance();
	delete SoundManager::instance();
	delete TextureManager::instance();
}

bool Engine::run(){
	while (!_input.shouldQuit() && (_stateMachine.getCurrent() != _stateMachine.getState("quit"))){
		float calculatedDeltatime = _deltaTimeInMilliseconds / 1000.0f;
		if (calculatedDeltatime < float(1/60)){ // around here.
			calculatedDeltatime = float(1/60); // the game breaks with a delta time lower than approximately this.
		}
		_input.EventLoop(CefManager::instance()->GetCefBrowser(), _display.getHandle());

		if (_input.doesWindowHaveFocus()){
			update(calculatedDeltatime);
		}
		else{
			SoundManager::instance()->haltChannel(-1);
			SoundManager::instance()->haltMusic();
		}
		draw();
		_current = SDL_GetTicks();
		_deltaTimeInMilliseconds = _current - _last;
		_last = _current;
	}
	return true;
}

void Engine::processArguments(int argc, char** argv){
	// do nothing for now.
}

// PRIVATE FUNCTIONS
void Engine::update(float dt){
	CefDoMessageLoopWork();
	if(!_input.shouldQuit() && (_stateMachine.getCurrent() != _stateMachine.getState("quit"))){ // safeguard line
		_stateMachine.update(dt);
		_renderer.update(dt);
	}
}

void Engine::draw(){
	_renderer.Clear(0.2, 0.2, 0.2, 1);
	_renderer.BlendingMode(BlendMode::AlphaBlending);

	_stateMachine.draw(&_renderer);
	if (GameVersionId == GameVersionPreview)
	_renderer.RenderText( Point{0, 0}, "Killbot Game by Xpost2000 : Preview for itch.io", "ocr", Color{255, 255, 255, 255}, 15 );
//	_renderer.RenderText( Point{0, 12}, "This build is the platformer demo.", "ocr", Color{255, 255, 255, 255} );
//	_renderer.RenderText( Point{0, 24}, "TODO: Finish the game and make more flexible.", "ocr", Color{255, 255, 255, 255} );

	_display.present();
}

void Engine::ApplyEngineSettings(int w, int h, bool fullscreen, bool vsync){
	_display.setVideoSettings(w, h, fullscreen, vsync);
	_renderer.init(w, h);
}