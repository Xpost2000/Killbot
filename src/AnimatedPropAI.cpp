#include "AnimatedPropAI.h"
#include "GameObject.h"

AnimatedPropAI::AnimatedPropAI(GameObject* parent, std::string animationGroupName, int loops, float speed) : AI(parent), _loopCount(loops), _speed(speed){
	_animation = *AnimationManager::instance()->getGroup(animationGroupName)->getAnimation("animation");
}

AnimatedPropAI::~AnimatedPropAI(){

}

void AnimatedPropAI::update(float dt, World& world){
	if (_currentLoops < _loopCount || _loopCount == -1){
		if (_animation.isFinished()){
			_currentLoops++;
			_animation.reset();
		}
		AI::getParent()->setTexture(_animation.getCurrentFrame()->getTexture());
		_animation.update(dt, _speed);
	}
	else{
		AI::getParent()->setHealth(-1); // "kill" it
	}
}