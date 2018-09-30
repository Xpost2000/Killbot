#include "IdleCommand.h"
#include "AnimationManager.h"

IdleCommand::IdleCommand(AI* _aiParent, float animationSpeed, std::string animationName) : Command(_aiParent), _animationSpeed(animationSpeed){
	_animation = *AnimationManager::instance()->getGroup(animationName)->getAnimation("idle");
}

IdleCommand::~IdleCommand(){
}

void IdleCommand::update(float dt, World& world){
	GameObject* parent = getParent()->getParent();
	parent->setTexture(_animation.getCurrentFrame()->getTexture());
	_animation.update(dt, _animationSpeed);
}
