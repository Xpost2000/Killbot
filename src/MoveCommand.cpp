#include "MoveCommand.h"
#include "AnimationManager.h"
#include "SoundManager.h"

MoveCommand::MoveCommand(AI* _aiParent, float maxSpeed, std::string animationName) : Command(_aiParent), _maxSpeed(maxSpeed){
	_animation = *AnimationManager::instance()->getGroup(animationName)->getAnimation("walk");
}

MoveCommand::~MoveCommand(){
}

void MoveCommand::update(float dt, World& world){
	GameObject* parent = getParent()->getParent();
	// I wanna disable the floatyness to
	// see how good it plays.
	switch(_direction){
		case 0:
				parent->getVelocity().x = -_maxSpeed;
				parent->flipX = true;
			break;
		case 1:
				parent->getVelocity().x = _maxSpeed;
				parent->flipX = false;
			break;
		default:
			break;
	}

	if(_animation.getCurrentFrameIndex() == 0){
			_playedSound = false;
	}

	if(_animation.getCurrentFrameIndex() == 4){
		if(!_playedSound){
			SoundManager::instance()->playSound( "audio/fx/step.wav" );
			_playedSound = true;
		}
	}

	parent->setTexture(_animation.getCurrentFrame()->getTexture());
	_animation.update(dt, 0.10);
}		
