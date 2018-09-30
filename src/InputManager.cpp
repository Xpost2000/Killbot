#include "InputManager.h"
#include "Engine.h"
#include "include\sdl_keyboard_utils.h"
#include <iostream>

InputManager::InputManager(){
	for(int i = 0; i < SDL_NUM_SCANCODES; ++i){
		_keysDown[i]=false;
		_keysPressed[i]=false;
	}
}

InputManager::~InputManager(){
}

int InputManager::EventLoop( CefRefPtr<CefBrowser> browser, SDL_Window* window ){
	int result;
	CefMouseEvent mouseEvent;
	CefKeyEvent keyEvent;
	while((result = SDL_PollEvent(&_event)) & result){
		switch(_event.type){
			case SDL_WINDOWEVENT:
				switch (_event.window.event){
				}
			break;
			case SDL_QUIT:
				_shouldQuit=true;
		//		browser->GetHost()->CloseBrowser(false);
				break;
			case SDL_KEYDOWN:
				_keysDown[_event.key.keysym.scancode]=true;
				if(!_event.key.repeat){
					if(_event.key.state == SDL_PRESSED){
						_keysPressed[_event.key.keysym.scancode]=true;
					}
				}else{
					_keysPressed[_event.key.keysym.scancode]=false;
				}

				keyEvent.modifiers = getKeyboardModifiers(_event.key.keysym.mod);
				keyEvent.windows_key_code = getWindowsKeyCode(_event.key.keysym);
				keyEvent.type = KEYEVENT_KEYDOWN;
				browser->GetHost()->SendKeyEvent(keyEvent);
				break;
			case SDL_KEYUP:
				_keysDown[_event.key.keysym.scancode]=false;
				_keysPressed[_event.key.keysym.scancode]=false;
				keyEvent.modifiers = getKeyboardModifiers(_event.key.keysym.mod);
				keyEvent.windows_key_code = getWindowsKeyCode(_event.key.keysym);
				keyEvent.type = KEYEVENT_KEYUP;
				browser->GetHost()->SendKeyEvent(keyEvent);
				break;
			case SDL_JOYBUTTONDOWN:
				break;
			case SDL_JOYDEVICEADDED:
				break;
			case SDL_JOYDEVICEREMOVED:
				break;
			case SDL_MOUSEMOTION:
				_mouseX = _event.motion.x;
				_mouseY = _event.motion.y;

				mouseEvent.x = ((float)_mouseX / (float)Engine::instance()->getDisplay()->getWidth()) * (float)1024;
				mouseEvent.y = ((float)_mouseY / (float)Engine::instance()->getDisplay()->getHeight()) * (float)768;
				browser->GetHost()->SendMouseMoveEvent(mouseEvent, false);
				break;
			case SDL_MOUSEBUTTONDOWN:
				mouseEvent.x = ((float)_mouseX / (float)Engine::instance()->getDisplay()->getWidth()) * (float)1024;
				mouseEvent.y = ((float)_mouseY / (float)Engine::instance()->getDisplay()->getHeight()) * (float)768;
				switch(_event.button.button){
					case SDL_BUTTON_LEFT:
						_mouseButtonsDown[0]=true;
						browser->GetHost()->SendMouseClickEvent(mouseEvent, MBT_LEFT, false, 1);
						break;
					case SDL_BUTTON_RIGHT:
						_mouseButtonsDown[1]=true;
						browser->GetHost()->SendMouseClickEvent(mouseEvent, MBT_RIGHT, false, 1);
						break;
					case SDL_BUTTON_MIDDLE:
						_mouseButtonsDown[2]=true;
						browser->GetHost()->SendMouseClickEvent(mouseEvent, MBT_MIDDLE, false, 1);
						break;
				}
				break;
			case SDL_MOUSEBUTTONUP:
				mouseEvent.x = ((float)_mouseX / (float)Engine::instance()->getDisplay()->getWidth()) * (float)1024;
				mouseEvent.y = ((float)_mouseY / (float)Engine::instance()->getDisplay()->getHeight()) * (float)768;
				switch(_event.button.button){
					case SDL_BUTTON_LEFT:
						_mouseButtonsDown[0]=false;
						browser->GetHost()->SendMouseClickEvent(mouseEvent, MBT_LEFT, true, 1);
						break;
					case SDL_BUTTON_RIGHT:
						_mouseButtonsDown[1]=false;
						browser->GetHost()->SendMouseClickEvent(mouseEvent, MBT_RIGHT, true, 1);
						break;
					case SDL_BUTTON_MIDDLE:
						_mouseButtonsDown[2]=false;
						browser->GetHost()->SendMouseClickEvent(mouseEvent, MBT_MIDDLE, true, 1);
						break;
				}
				break;
			case SDL_MOUSEWHEEL:
				break;
			case SDL_TEXTEDITING:
				break;
			default:break;
		}
	}
	return result;
}

bool InputManager::isAnyKeyPressed(){
	// this is legit a bad idea cause it's slow
	// but it achieves it's purpose correctly
	for(int i = 0; i < SDL_NUM_SCANCODES; ++i){
		if(isKeyDown(i) || isKeyPressed(i)){
			return true;
		}
	}
	return false;
}

bool InputManager::isKeyDown( int scancode ){
	return _keysDown[scancode];
}

bool InputManager::isKeyUp( int scancode ){
	return !_keysDown[scancode];
}

bool InputManager::isKeyPressed( int scancode ){
	if(_keysPressed[scancode]){ 
		_keysPressed[scancode] = false; 
		return true; 
	}else{
		return false;
	}
}
