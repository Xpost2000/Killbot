#ifndef ANIMATION_MANAGER_H
#define ANIMATION_MANAGER_H

#include <map>
#include <string>
#include "Animation.h"

class AnimationManager{
	public:
		AnimationManager();
		~AnimationManager();
		static AnimationManager* instance(){
			if(_instance == nullptr) _instance = new AnimationManager();
			return _instance;
		}

		AnimationGroup* addGroup(std::string name);
		AnimationGroup* getGroup(std::string name);

	private:
		std::map<std::string, AnimationGroup*> _animations;
		static AnimationManager* _instance;
};

#endif
