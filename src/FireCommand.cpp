#include "FireCommand.h"
#include "AnimationManager.h"
#include "SoundManager.h"
#include "constants.h"
#include "Engine.h"

#include "GameObjectFactory.h"
#include <cstdio>

FireCommand::FireCommand(AI* aiParent, int fireFrame, std::string animationName) : Command(aiParent), _fireFrame(fireFrame){
	_animation = *AnimationManager::instance()->getGroup(animationName)->getAnimation("fire");
}

FireCommand::~FireCommand(){
}

void FireCommand::update(float dt, World& world){
	GameObject* parent = getParent()->getParent();
	parent->getVelocity().x = 0; // no sliding.
	if(_animation.getCurrentFrameIndex() == _fireFrame){
		if(_fired == false){
			_fired = true;
			parent->getVelocity().x = (_bullet.pushPower * (parent->flipX ? 1 : -1));
			switch (parent->flipX){
			case false:
				world.AddEntity(GameObjectFactory::instance()->createBullet(parent, Point{ parent->getPosition().x + parent->getSize().x, parent->getPosition().y + parent->getSize().y / 2 }, _bullet.size, _bullet.tex, _bullet.speed, _bullet.damage, _bullet.pushPower, _bullet.explosive, _bullet.explosiveRange));
				break;
			case true:
				world.AddEntity(GameObjectFactory::instance()->createBullet(parent, Point{ parent->getPosition().x, parent->getPosition().y + parent->getSize().y / 2 }, _bullet.size, _bullet.tex, _bullet.speed, _bullet.damage, _bullet.pushPower, _bullet.explosive, _bullet.explosiveRange));
				break;
			}
			Engine::instance()->getRenderer()->ScreenShake(0.25, 1.25, 1.25);
			SoundManager::instance()->playSound("audio/fx/fire_cannon.wav", 100, -1);
		}
	}

	parent->setTexture(_animation.getCurrentFrame()->getTexture());
	_animation.update(dt, _fireSpeed);
}
		
