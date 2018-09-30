#include "Display.h"
#include <iostream>
#include <GL/glew.h>

Display::Display(std::string name, int w, int h, bool fullscreen){
	init(name, w, h, fullscreen);
}

Display::~Display(){
	SDL_GL_DeleteContext(_gl);

	if(_window)
	SDL_DestroyWindow(_window);
}

void Display::init(std::string name, int w, int h, bool fullscreen){
	_w = w;
	_h = h;
	_fullscreen = fullscreen;
	_name = name;

	_window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_OPENGL);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	_gl = SDL_GL_CreateContext(_window);

	glewInit();
}

void Display::present(){
	SDL_GL_SwapWindow(_window);
}

void Display::setVideoSettings(int w, int h, bool fullscreen, bool vsync){
	SDL_DisplayMode mode{ SDL_PIXELFORMAT_RGBA32, w, h, 60, 0 };
	_w = w;
	_h = h;
	SDL_SetWindowSize(getHandle(), w, h);
	SDL_SetWindowDisplayMode(getHandle(), &mode);
	SDL_SetWindowFullscreen(getHandle(), fullscreen ? SDL_WINDOW_FULLSCREEN : 0);
	SDL_GL_SetSwapInterval(vsync ? 1 : 0);
}