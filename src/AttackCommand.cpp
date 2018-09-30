#include "AttackCommand.h"
#include "AnimationManager.h"
#include "SoundManager.h"
#include "constants.h"

#include "Engine.h"

#include "GameObjectFactory.h"
#include <cstdio>

AttackCommand::AttackCommand(AI* aiParent, int fireFrame, std::string animationName) : Command(aiParent), _attackFrame(fireFrame){
	_animation = *AnimationManager::instance()->getGroup(animationName)->getAnimation("attack");
}

AttackCommand::~AttackCommand(){
}

void AttackCommand::update(float dt, World& world){
	GameObject* parent = getParent()->getParent();
	parent->getVelocity().x = 0; // no sliding.
	if(_animation.getCurrentFrameIndex() == _attackFrame){
		if(_attack == false){
			_attack = true;
			_corpseSpawned = false;
			//world.AddEntity(GameObjectFactory::instance()->createBullet(parent, Point{ parent->getPosition().x + parent->getSize().x,parent->getPosition().y + parent->getSize().y/2}, _bullet.size, _bullet.tex, _bullet.speed, _bullet.damage, _bullet.pushPower, _bullet.explosive, _bullet.explosiveRange));
			for (auto &ent : world.getEntities()){
				if (ent != parent && (ent->getType() == GameObjectTypeEnemy || ent->getType() == GameObjectTypePlayer)){
					GameObject hitBox(Point{ parent->getHitBoxPos().x, parent->getHitBoxPos().y }, Point{ _radiusOfHitX, _radiusOfHitY });
					if (hitBox.collide(*ent)){
						ent->flash();
						// push power is fixed for now
						switch (parent->flipX){
						case true:
							ent->getVelocity().x = -150;
							break;
						case false:
							ent->getVelocity().x = 150;
							break;
						}
						ent->getHealth() -= _damage;
						SoundManager::instance()->playSound("audio/fx/hit.wav", 100, -1);
						Engine::instance()->getRenderer()->ScreenShake(0.15, 1.35, 1.35);
						if (ent->getHealth() < 0){
							if (_corpseSpawned == false){
								GameObject* corpseObject = GameObjectFactory::instance()->createProp(ent->getPosition(), Point{ ent->getSize().x - 3, ent->getSize().y - 15 }, TextureManager::instance()->getTexture("tex/killbot_corpse.png"), true, false);
								corpseObject->flipX = ent->flipX;
								world.AddEntity(corpseObject);
								_corpseSpawned = true;
							}
						}
					}
				}
			}
		}
	}

	parent->setTexture(_animation.getCurrentFrame()->getTexture());
	_animation.update(dt, _attackSpeed);
}
		
