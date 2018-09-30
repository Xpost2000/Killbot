#ifndef DISPLAY_H
#define DISPLAY_H

#include <string>
#include <SDL2/SDL.h>

class Display{
	public:
		Display(std::string name, int w, int h, bool fullscreen=false);
		Display() = default;
		~Display();

		// for two step initialization
		void init(std::string name, int w, int h, bool fullscreen=false);
		void present();

		std::string getName() { return _name; }
		const int getWidth()  const { return _w; }
		const int getHeight() const { return _h; }
		const bool isFullscreen() const { return _fullscreen; }
		void setVideoSettings(int w, int h, bool fullscreen, bool vsync);

		SDL_Window* getHandle() { return _window; }

	private:
		SDL_Window* _window = nullptr;
		SDL_GLContext _gl;
		
		std::string _name;
		int _w, _h;
		bool _fullscreen=false;
};

#endif
