#include "BasicEnemyAI.h"
#include "GameObject.h"
#include "RandomNumberGenerator.h"
#include "AnimationManager.h"
#include "constants.h"

#include <cstdio>

BasicEnemyAI::BasicEnemyAI(GameObject* parent, float maxSpeed, float dmg, std::string animationGroup) : EntityMovingBaseAI(parent){
	moveCommand = MoveCommand(this, maxSpeed, animationGroup);
	idleCommand = IdleCommand(this, 0.14, animationGroup);
	jumpCommand = JumpCommand(this, -440, -440);
	attackCommand = AttackCommand(this, 2, animationGroup);
	attackCommand.setAttackSpeed(0.15);
	attackCommand.setDamage(dmg);
	jumpCommand.setMaxJumps(2);

	_commandDelay = RandomFloat(0.35, 1.25).get();
}

BasicEnemyAI::~BasicEnemyAI(){

}

void BasicEnemyAI::ai_update(float dt, World& world){
	GameObject* parent = AI::getParent();

	// yay rng to the rescue.
	if (_commandDelay > 0){
		_commandDelay -= dt;
	}
	if (_jumpDelay > 0){
		_jumpDelay -= dt;
	}
	RandomInt decisionMaker(1, 7);
	if (attackCommand.isFinished() && _currentCommand == &attackCommand){
		_currentCommand = &idleCommand;
		attackCommand.reset();
	}
	if (_currentCommand == &jumpCommand){
		_currentCommand = &idleCommand;
	}
	switch (decisionMaker()){
		// TODO: Make better.
	case 1:
		if (_commandDelay <= 0 && _jumpDelay <= 0){
			if (attackCommand.isFinished() || _currentCommand != &attackCommand){
				if (_currentCommand != &jumpCommand){
					_currentCommand = &jumpCommand;
					_jumpDelay = RandomFloat(2, 3.5).get();
				}
			}
		}
		break;
	case 2:
		if (_commandDelay <= 0){
			if (attackCommand.isFinished() || _currentCommand != &attackCommand){
				_flip = !_flip;
				_commandDelay = RandomFloat(0.35, 0.5).get();
			}
		}
		break;
	case 7:
	case 3:
		if (_commandDelay <= 0){
			if (_currentCommand != &attackCommand){
				_currentCommand = &attackCommand;
			//	fireCommand.setCurrentBullet(_bullet);
			}
		}
		break;
	case 6:
	case 4:
		if (_commandDelay <= 0){
			if (attackCommand.isFinished() || _currentCommand != &attackCommand){
				_currentCommand = &moveCommand;
				attackCommand.reset();
			}
			_commandDelay = RandomFloat(1.3, 3.0).get();
		}
		break;
	case 5:
		if (attackCommand.isFinished() && _currentCommand != &attackCommand){
			_currentCommand = &idleCommand;
		}
		break;
	}


	// jump
	moveCommand.setDirection(_flip);
	attackCommand.setDirection(_flip);

	if (!xCollided){
		_flip = !_flip;
	}

	if (_onGround){
		jumpCommand.reset();
	}

	parent->setHitBox(Point{ parent->getPosition().x + parent->getSize().x*0.05, parent->getPosition().y }, Point{ parent->getSize().x*0.80, parent->getSize().y });
	attackCommand.setRadiusX(parent->getHitBoxSize().x*0.94);
	attackCommand.setRadiusY(parent->getHitBoxSize().y);
}
