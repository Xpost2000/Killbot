#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H
#include <SDL2/SDL.h>
#include "wrapper/cef_helpers.h"
#include "include/cef_app.h"
#define MOUSEBUTTON_LEFT 0
#define MOUSEBUTTON_RIGHT 1
#define MOUSEBUTTON_MIDDLE 2

/*
 * A basic input manager class
 * it's pretty crappy, but it gets the job done
 *
 * TODO: Implement text typing / editing
 * 	 functions using SDL2's SDL_StartTextInput()
 *
 * 	 just like check these pages for help
 *
 * 	 https://wiki.libsdl.org/SDL_TextEditingEvent
 * 	 https://wiki.libsdl.org/SDL_StartTextInput
 * 	 https://wiki.libsdl.org/SDL_IsTextInputActive
 */

class InputManager{
	public:
		InputManager( const InputManager& ) = default;
		InputManager();
		~InputManager();

		int  EventLoop( CefRefPtr<CefBrowser> browser, SDL_Window* window );

		bool doesWindowHaveFocus() { return _hasFocus; }
		bool shouldQuit() { return _shouldQuit; }

		bool isKeyDown   ( int scancode );
		bool isKeyUp     ( int scancode );
		bool isKeyPressed( int scancode );
		bool isAnyKeyPressed( );

		int  getMouseX() { return _mouseX; }
		int  getMouseY() { return _mouseY; }

		bool isMouseButtonDown( int which ) { return _mouseButtonsDown[which]; }
	protected:
	private:
//		uint32_t _mouseState;
		int _mouseX=0, _mouseY=0;

		bool _hasFocus = true;
		bool _keysDown[SDL_NUM_SCANCODES];
		bool _keysPressed[SDL_NUM_SCANCODES];
		bool _mouseButtonsDown[3]; // left, right, middle.

		bool _shouldQuit=false;
		SDL_Event _event;
};
#endif
