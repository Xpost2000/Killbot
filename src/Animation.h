#ifndef ANIMATION_H
#define ANIMATION_H

#include "Point.h"
#include "Texture.h"
#include <iostream>
#include <map>

#include <string>
#include <vector>

/*
 * This file contains everything to do
 * with animations. So anything that starts
 * with animation.
 */

// sprite based.

class AnimationEvent{
	public:
		AnimationEvent();
		~AnimationEvent();
		virtual void executeEvent(float dt){ }
	protected:
	private:
};

class AnimationPlaySoundEvent : public AnimationEvent{
	public:
		AnimationPlaySoundEvent() = default;
		AnimationPlaySoundEvent(std::string soundPath, int volume, int channel);	
		~AnimationPlaySoundEvent(){}
		void executeEvent(float dt) override;
	private:
		int _volume = 0;
		int _channel = 0;
		std::string _sndPath;
};

class AnimationFrame{
	public:
		AnimationFrame(Texture* tex, UV uvs);
		~AnimationFrame();

		void addEvent( AnimationEvent* event );

		Texture* getTexture() { return _texture; }
		UV getUvs(){ return _uvs; }
	private:
		friend class Animation;
		void executeEvents(float dt);

		UV _uvs;

		std::vector<AnimationEvent*> _events;
		Texture* _texture = nullptr;
};

class Animation{
	public:
		Animation();
		~Animation();
		// basically for a sprite sheet or something.
		void addFrame( Texture* tex, UV uvs );
		void addFrame( Texture* tex );
		void deallocate();

		void addEvent( int frame, AnimationEvent* event ); //EVNT OBJ );

		void update(float dt, float spf);

		AnimationFrame* getCurrentFrame();
		int getCurrentFrameIndex() { return _currentFrame; }
		int isFinished() { return _currentFrame >= _maxFrame-1; }
		void reset() { _currentFrame = 0; _counter = 0;}
	private:
		float _counter = 0.0f;
		int   _currentFrame =0;
		int   _maxFrame = 0;
		std::vector<AnimationFrame*> _frames;
};

// a container for related animations. :D
class AnimationGroup{
	public:
		AnimationGroup();
		~AnimationGroup();
		Animation* addAnimation(std::string name);
		Animation* getAnimation(std::string name);
	private:
		std::map<std::string, Animation*> _animations;
};

#endif
