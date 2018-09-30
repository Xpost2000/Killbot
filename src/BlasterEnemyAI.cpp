#include "BlasterEnemyAI.h"
#include "GameObject.h"

#include "AnimationManager.h"
#include "constants.h"

#include <cstdio>

BlasterEnemyAI::BlasterEnemyAI(GameObject* parent, float maxSpeed, std::string animationGroup) : EntityMovingBaseAI(parent){
	moveCommand = MoveCommand(this, maxSpeed, animationGroup);
	idleCommand = IdleCommand(this, 0.14, animationGroup);
	jumpCommand = JumpCommand(this, -440, -440);
	fireCommand = FireCommand(this, 2, animationGroup);

	fireCommand.setFireSpeed(0.20);

	jumpCommand.setMaxJumps(2);

	_commandDelay = RandomFloat(0.35, 1.25).get();

//	_currentCommand = &moveCommand;
}

BlasterEnemyAI::~BlasterEnemyAI(){

}

void BlasterEnemyAI::ai_update(float dt, World& world){
	GameObject* parent = AI::getParent();

	// yay rng to the rescue.
	if(_commandDelay > 0){
		_commandDelay -= dt;
	}
	if (_jumpDelay > 0){
		_jumpDelay -= dt;
	}
	RandomInt decisionMaker(1, 7);
	if (fireCommand.isFinished() && _currentCommand == &fireCommand){
		_currentCommand = &idleCommand;
		fireCommand.reset();
	}
	if (_currentCommand == &jumpCommand){
		_currentCommand = &idleCommand;
	}
	switch(decisionMaker()){
			// TODO: Make better.
			case 1:
				if(_commandDelay <= 0 && _jumpDelay <= 0){
					if (fireCommand.isFinished() || _currentCommand != &fireCommand){
						if (_currentCommand != &jumpCommand){
							_currentCommand = &jumpCommand;
							_jumpDelay = RandomFloat(2, 3.5).get();
						}
					}
				}
				break;
			case 2:
				if (_commandDelay <= 0){
					if (fireCommand.isFinished() || _currentCommand != &fireCommand){
						_flip = !_flip;
						_commandDelay = RandomFloat(0.35, 0.5).get();
					}
				}
				break;
			case 7:
			case 6:
			case 3:
				if (_commandDelay <= 0){
					if (_currentCommand != &fireCommand){
						_currentCommand = &fireCommand;
						fireCommand.setCurrentBullet(_bullet);
					}
				}
				break;
			case 4:
				if (_commandDelay <= 0){
					if (fireCommand.isFinished() || _currentCommand != &fireCommand){
						_currentCommand = &moveCommand;
						fireCommand.reset();
					}
					_commandDelay = RandomFloat(1.3, 3.0).get();
				}
				break;
			case 5:
				if (fireCommand.isFinished() && _currentCommand != &fireCommand){
					_currentCommand = &idleCommand;
				}
			break;	
		}


	// jump
	moveCommand.setDirection(_flip);
	fireCommand.setDirection(_flip);

	if(!xCollided){
		_flip = !_flip;
	}

	if(_onGround){
		jumpCommand.reset();
	}

	parent->setHitBox(Point{parent->getPosition().x+parent->getSize().x*0.05, parent->getPosition().y}, Point{parent->getSize().x*0.80, parent->getSize().y});
}
