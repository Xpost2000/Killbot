/*
 * KILLBOT
 * 
 * is an open source game about robot survival.
 * You play as a killbot in a small arena in which
 * other killbots are sent to destroy you. For the
 * moment killbots aren't very strong and have strength
 * in numbers.
 *
 * You have a cannon. Use it effectively
 */
#include "Engine.h"
#include "include\cef_app.h"

int main(int argc, char** argv){
	//CefManager::instance()->getSettings().windowless_rendering_enabled = true;
	int result = CefManager::instance()->InitializeCEF(argc, argv);
	if (result >= 0){
		return result;
	}
	Engine::InitSDL();
	SDL_DisplayMode desktopDisplay;
	// should usually adopt the desktop display mode .
	SDL_GetDesktopDisplayMode(0, &desktopDisplay);
	// this is for the preview version
	if (GameVersionId == GameVersionPreview || GameVersionId == GameVersionFinal){
		// start fullscreen, or just read from a cfg file....
		Engine::Init("Killbot Engine", desktopDisplay.w, desktopDisplay.h, true);
	}
	else if (GameVersionId == GameVersionDeveloper){
		Engine::Init("Killbot Engine", 1024, 768, false);
	}
	Engine* gameEngine = Engine::instance();
	gameEngine->processArguments(argc, argv);
	gameEngine->run();
	delete gameEngine;

	Engine::QuitSDL();
	CefManager::instance()->ShutdownCEF();
	return 0;
}
