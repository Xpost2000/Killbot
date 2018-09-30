#include "AnimationManager.h"
AnimationManager* AnimationManager::_instance = nullptr;

AnimationManager::AnimationManager(){
}

AnimationManager::~AnimationManager(){
	for(auto& anim : _animations){
		delete anim.second;
	}
}

AnimationGroup* AnimationManager::addGroup(std::string name){
	_animations.emplace(name, new AnimationGroup());
	return _animations[name];
}

AnimationGroup* AnimationManager::getGroup(std::string name){
	if(!_animations.count(name)){
		return addGroup(name);
	}else{
		return _animations[name];
	}
}
