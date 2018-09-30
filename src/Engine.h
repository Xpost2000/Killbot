#ifndef ENGINE_H
#define ENGINE_H

#include "Renderer2D.h"
#include "Display.h"

#include "AnimationManager.h"
#include "InputManager.h"
#include "TextureManager.h"
#include "SoundManager.h"

#include "GameUpgradeScreenState.h"
#include "MainMenuState.h"
#include "LoadingScreenState.h"
#include "IntroState.h"
#include "GameOverState.h"
#include "EndGameState.h"
#include "CreditsState.h"
#include "GameState.h"
#include "StateMachine.h"

#include "CefManager.h"

// the game effectively runs here.
/*
	I may have to convert this to singleton so the CEF message handler
	can affect the engine.
*/
class Engine{
	public:
		Engine(){}
		Engine(std::string name, int w, int h, bool fullscreen);
		~Engine();

		void processArguments(int argc, char** argv);
		bool run();

		static void InitSDL(){
			SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
			Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG);
			Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
		}

		static void QuitSDL(){
			Mix_CloseAudio();
			Mix_Quit();
			SDL_Quit();
		}

		static void Init(std::string name, int w, int h, bool fullscreen){
			_instance = new Engine(name, w, h, fullscreen);
		}

		static Engine* instance(){
			return _instance;
		}

		Renderer2D* getRenderer(){ return &_renderer; }
		Display* getDisplay() { return &_display; }

		int getNumOfDisplayModes(){ return SDL_GetNumDisplayModes(0); }
		std::vector<SDL_DisplayMode> getDisplayModes(){
			std::vector<SDL_DisplayMode> displayModes;
			for (int i = 0; i < getNumOfDisplayModes(); ++i){
				displayModes.push_back(SDL_DisplayMode{ SDL_PIXELFORMAT_UNKNOWN, 0, 0, 0 ,0});
				SDL_GetDisplayMode(0, i, &displayModes[i]);
			}
			return displayModes;
		}

		void ApplyEngineSettings(int w, int h, bool fullscreen, bool vsync);
	private:
		void update(float dt);
		void draw();
	private:
		friend class BrowserClient;

		static Engine* _instance;
		//TODO put in timer class
		std::string _basePath;

		Uint32 _current=0, _last=0, _deltaTimeInMilliseconds=0;

		Renderer2D _renderer;
		InputManager _input;
		Display _display;

		StateMachine _stateMachine;
};
#endif
