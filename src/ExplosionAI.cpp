#include "ExplosionAI.h"
#include "GameObject.h"
#include "GameObjectFactory.h"
#include "SoundManager.h"

#include "Engine.h"

#include "RandomNumberGenerator.h"

ExplosionAI::ExplosionAI(GameObject* parent, float radius, float damage, std::string animationGroup) : AI(parent), _radius(radius), _damage(damage){
	_animation = AnimationManager::instance()->getGroup(animationGroup)->getAnimation("animation");
}

ExplosionAI::~ExplosionAI(){

}

void ExplosionAI::update(float dt, World& world){
	GameObject* parent = AI::getParent();
	if (_hurtAlready){
		parent->setHealth(-1);
	}
	else{
		// make explosion
		GameObject explosion(Point{ parent->getPosition().x - _radius / 2, parent->getPosition().y - _radius / 2 }, Point{ _radius, _radius }); // collision object
		SoundManager::instance()->playSound("audio/fx/explode.wav", 100, -1);
		Engine::instance()->getRenderer()->ScreenShake(0.75, 3.5, 3.5);
		world.AddEntity(GameObjectFactory::instance()->createAnimationProp(Point{ parent->getPosition().x - _radius / 2, parent->getPosition().y - _radius / 2 }, Point{ _radius, _radius }, "explosion", 0.05, 1));
		for (auto& ent : world.getEntities()){
			if (ent != &explosion){
				if (explosion.collide(*ent)){
					if (ent->getType() == GameObjectTypeEnemy || ent->getType() == GameObjectTypePlayer){
						ent->getHealth() -= _damage;
						ent->flash();
						if (ent->getHealth() <= 0){
							// GIB!
							GameObject* head = GameObjectFactory::instance()->createProp(ent->getPosition(), ent->getSize(), TextureManager::instance()->getTexture("tex/gibs/killbot-head.png"), true, false);
							GameObject* body = GameObjectFactory::instance()->createProp(ent->getPosition(), ent->getSize(), TextureManager::instance()->getTexture("tex/gibs/killbot-body.png"), true, false);
							GameObject* l_leg = GameObjectFactory::instance()->createProp(ent->getPosition(), ent->getSize(), TextureManager::instance()->getTexture("tex/gibs/killbot-foot.png"), true, false), *r_leg = GameObjectFactory::instance()->createProp(ent->getPosition(), ent->getSize(), TextureManager::instance()->getTexture("tex/gibs/killbot-foot.png"), true, false);
							head->getVelocity().x = RandomFloat(-100, 100).get();
							head->getVelocity().y = RandomFloat(-70, 0).get();

							body->getVelocity().x = RandomFloat(-100, 100).get();
							body->getVelocity().y = RandomFloat(-70, 0).get();

							l_leg->getVelocity().x = RandomFloat(-100, 100).get();
							l_leg->getVelocity().y = RandomFloat(-70, 0).get();

							r_leg->getVelocity().x = RandomFloat(-100, 100).get();
							r_leg->getVelocity().y = RandomFloat(-70, 0).get();

							world.AddEntity(head);
							world.AddEntity(body);
							world.AddEntity(l_leg);
							world.AddEntity(r_leg);
						}
						//TODO: Push back!
					}
				}
			}
		}
		_hurtAlready = true;
	}
}