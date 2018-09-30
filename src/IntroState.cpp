#include "IntroState.h"
#include "StateMachine.h"
#include "constants.h"
#include "SoundManager.h"

IntroState::IntroState(InputManager* input) : _input(input){
	_introAnimation = AnimationManager::instance()->getGroup(GameIntroAnimationGroupName)->getAnimation("intro");
}

IntroState::~IntroState(){

}

void IntroState::init(){

}

void IntroState::update(float dt){
	if (dt > 1){
		dt = 0; // I'm not even joking.
		/*
		Delta time is the amount of time between
		the last frame and the current frame
		( in seconds ).
		The loading screen makes it a few seconds
		which makes the first frame not appear.

		I reset it to zero so it actually
		works properly.
		*/
	}
	if (!SoundManager::instance()->isMusicPlaying())
		SoundManager::instance()->playMusic("audio/music/intro_music.ogg", 100, -1);
	if (GameVersionId == GameVersionDeveloper){
		_parent->setCurrent("mainMenu");
	}
	else if (GameVersionId == GameVersionFinal || GameVersionId == GameVersionPreview){
		if (!_introAnimation->isFinished()){
			_introAnimation->update(dt, 4.25);
		}
		else{
			if (_endPadding <= 0){
				_parent->setCurrent("mainMenu");
			}
			else{
				// this is to compensate for my broken animation system.
				_endPadding -= dt;
			}
		}
	}
	if (_input->isKeyPressed(SDL_SCANCODE_RETURN)){
		_parent->setCurrent("mainMenu");
	}
	if (_alphaForText < 255){
		if (dt < 2)
		_alphaForText += dt * 40;
	}
}

void IntroState::draw(Renderer2D* renderer){
	renderer->BlendingMode(BlendMode::AlphaBlending);
	renderer->RenderRectangle(*_introAnimation, Point{ 0, 0 }, Point{ 1024, 768 }, Color{255, 255, 255, 255});
	renderer->RenderText(Point{ 0, 0 }, "Press the Enter key to skip.", "OCR", Color{ _alphaForText, _alphaForText, _alphaForText, 0 }, 20);
	//renderer->RenderText(Point{ 0, 25 }, std::to_string(_alphaForText), "OCR", Color{ 255, 255, 255, 0 }, 20);
}

bool IntroState::OnEnter(){
	SoundManager::instance()->haltMusic();
	return true;
}

bool IntroState::OnExit(){
	SoundManager::instance()->haltMusic();
	return true;
}