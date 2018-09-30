#include "PlayerAI.h"
#include "GameObject.h"

#include "AnimationManager.h"
#include "constants.h"
#include "SoundManager.h"
#include "GameObjectFactory.h" // oh dear god...

#include <algorithm>

PlayerAI::PlayerAI(GameObject* parent, InputManager* input, std::string animationGroup) : EntityMovingBaseAI(parent), _input(input){	
	moveCommand = MoveCommand(this, 350, animationGroup);
	idleCommand = IdleCommand(this, 0.12, animationGroup);
	jumpCommand = JumpCommand(this, -400, -400);
	fireCommand = FireCommand(this, 2, animationGroup);
	attackCommand = AttackCommand(this, 2, animationGroup);
	attackCommand.setAttackSpeed(0.09);
	attackCommand.setDamage(35);
	// a more fairer armory to start with.
	reset();

	//TODO: Add power ups / upgrades to make it stronger
	fireCommand.setFireSpeed(0.15);

	jumpCommand.setMaxJumps(3);
}

PlayerAI::~PlayerAI(){

}

void PlayerAI::ai_update(float dt, World& world){
	GameObject* parent = AI::getParent();

	if(allowControl){
		_currentCommand = &idleCommand;
	}
	//TODO: Also check if I'm also on ground

	if(_input->isKeyDown(SDL_SCANCODE_A)){
		if(allowControl)
			_currentCommand = &moveCommand;
		moveCommand.setDirection(0);
		fireCommand.setDirection(0);
	}else if(_input->isKeyDown(SDL_SCANCODE_D)){
		if(allowControl)
			_currentCommand = &moveCommand;
		moveCommand.setDirection(1);
		fireCommand.setDirection(1);
	}else{
		moveCommand.reset();
		if(_onGround){
			if(allowControl)
			parent->getVelocity().x = 0;
		}else{
		}
	}
	
	if(_input->isKeyPressed(SDL_SCANCODE_E)){
		if (bullet_count[current_bullet_index] > 0){
			if (allowControl)
			if (_currentCommand != &fireCommand){
				_currentCommand = &fireCommand;
				bullet_count[current_bullet_index]--;
				FireCommandBullet whatBullet;

				// dear god, why is this code so horrendous?
				switch (current_bullet_index){
				case 0:
					whatBullet = GameObjectFactory::instance()->generateRubberBullet(GameObjectTypePlayer);
					break;
				case 1:
					whatBullet = GameObjectFactory::instance()->generateLeadBullet(GameObjectTypePlayer);
					break;
				case 2:
					whatBullet = GameObjectFactory::instance()->generateSilverBullet(GameObjectTypePlayer);
					break;
				case 3:
					whatBullet = GameObjectFactory::instance()->generateGoldBullet(GameObjectTypePlayer);
					break;
				case 4:
					whatBullet = GameObjectFactory::instance()->generateRocketBullet(GameObjectTypePlayer);
					break;
				}

				fireCommand.setCurrentBullet(
					whatBullet
					);
				allowControl = false;
			}
		}
		else{
			SoundManager::instance()->playSound("audio/fx/no_ammo.wav");
		}
	}

	if (_input->isKeyPressed(SDL_SCANCODE_W)){
		current_bullet_index++;
		current_bullet_index = std::min<int>(current_bullet_index, bullet_types-1);
		SoundManager::instance()->playSound("audio/fx/weapon_swap.wav");
	}
	if (_input->isKeyPressed(SDL_SCANCODE_S)){
		current_bullet_index--;
		current_bullet_index = std::max<int>(current_bullet_index, 0);
		SoundManager::instance()->playSound("audio/fx/weapon_swap.wav");
	}

	if(_input->isKeyPressed(SDL_SCANCODE_SPACE)){
		if ((allowControl)){
				_currentCommand = &jumpCommand;
		}
	}
	if (_input->isKeyPressed(SDL_SCANCODE_LCTRL)){
		if ((allowControl)){
			if (_currentCommand != &attackCommand){
				attackCommand.reset();
				//attackCommand.setDirection(parent->flipX);
				_currentCommand = &attackCommand;
				allowControl = false;
			}
		}
	}
	if (_currentCommand == &attackCommand){
		if (attackCommand.isFinished()){
			allowControl = true;
			attackCommand.reset();
			_currentCommand = &idleCommand;

		}
	}
	if(_currentCommand == &fireCommand){
		if(fireCommand.isFinished()){
			allowControl = true;
			fireCommand.reset();
			_currentCommand = &idleCommand;
		}
	}

	if(_onGround){
		jumpCommand.reset();
	}

	parent->setHitBox(Point{parent->getPosition().x+parent->getSize().x*0.05, parent->getPosition().y}, Point{parent->getSize().x*0.80, parent->getSize().y});
	attackCommand.setRadiusX(parent->getHitBoxSize().x*0.94);
	attackCommand.setRadiusY(parent->getHitBoxSize().y);
}
