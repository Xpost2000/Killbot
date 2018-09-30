#include "Animation.h"
#include "SoundManager.h"

#include <Windows.h>

AnimationEvent::AnimationEvent(){
}

AnimationEvent::~AnimationEvent(){
}

AnimationPlaySoundEvent::AnimationPlaySoundEvent(std::string soundPath, int volume, int channel) : AnimationEvent(), _sndPath(soundPath), _volume(volume), _channel(channel){
}

void AnimationPlaySoundEvent::executeEvent(float dt){
	if(_channel != -1){
		if(!SoundManager::instance()->isChannelPlaying(_channel)){
			SoundManager::instance()->playSound( _sndPath, _volume, _channel, 0 );
		}
	}else{
		SoundManager::instance()->playSound( _sndPath, _volume, _channel, 0 );
	}
}

AnimationFrame::AnimationFrame( Texture* tex, UV uvs ) : _texture(tex), _uvs(uvs){
}

AnimationFrame::~AnimationFrame(){
	for(auto& event : _events){
		delete event;
	}
}

void AnimationFrame::addEvent( AnimationEvent* event ){
	_events.push_back(event);
}

void AnimationFrame::executeEvents(float dt){
	// I mean I'm really only using these to
	// play like sounds so it doesn't
	// need delta time but just incase.
//	for(auto &ev : _events)
//		ev->executeEvent(dt);
}

Animation::Animation(){
}

Animation::~Animation(){
}

void Animation::addFrame(Texture* tex, UV uvs){
	_frames.push_back( new AnimationFrame(tex, uvs) );
	_maxFrame++;
}

void Animation::addFrame(Texture* tex){
	addFrame(tex, UV{0, 0, 1, 1});
}

void Animation::addEvent( int frame, AnimationEvent* event ){
	_frames[frame]->addEvent(event);
}

AnimationFrame* Animation::getCurrentFrame(){
	return _frames[_currentFrame];
}

void Animation::update(float dt, float spf){
	if(_currentFrame >= _maxFrame-1){
		_counter = 0;
		_currentFrame = 0;
	}else{
		_counter += dt;
		_currentFrame = _counter/spf;
		_frames[_currentFrame]->executeEvents(dt);
	}
	//MessageBox(NULL, std::to_string(_currentFrame).c_str(), "Current Frame", MB_ICONERROR);
}

void Animation::deallocate(){
	for(auto & f : _frames){
		delete f;
	}
}

AnimationGroup::AnimationGroup(){

}

AnimationGroup::~AnimationGroup(){
	for (auto& anim : _animations){
		anim.second->deallocate();
		delete anim.second;
	}
}

Animation* AnimationGroup::addAnimation(std::string name){
	_animations.emplace(name, new Animation());
	return _animations[name];
}

Animation* AnimationGroup::getAnimation(std::string name){
	if (!_animations.count(name)){
		return addAnimation(name);
	}
	else{
		return _animations[name];
	}
}