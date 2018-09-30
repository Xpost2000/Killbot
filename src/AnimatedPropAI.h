#ifndef ANIMATED_PROP_H
#define ANIMATED_PROP_H

#include "AnimationManager.h"
#include "AI.h"

/*
If I made a particle system it might alleivate my animation worries.
Actually I should but I screwed up the last one on accident.

This AI simply loops through an animation nth times before deletion
*/

class AnimatedPropAI : public AI{
	public:
		// -1 equals infinite loops
		AnimatedPropAI(GameObject* parent, std::string animationGroupName, int loops, float speed);
		~AnimatedPropAI();
		void update(float dt, World& world);
	private:
		float _speed = 0;
		int _currentLoops = 0;
		int _loopCount = 0;
		Animation _animation;
};

#endif