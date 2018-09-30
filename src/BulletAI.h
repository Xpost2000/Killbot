#ifndef BULLET_H
#define BULLET_H

#include "AI.h"
#include "Texture.h"

class BulletAI : public AI{
	public:
		BulletAI(GameObject* parentOfBullet, GameObject* parent, int dmg, Point speed, float pushForce, Texture* texture, bool explosive=false, float explosionRadius= 0);
		~BulletAI();
		void update(float dt, World& world);
		void setDirection(int direction) { _direction = direction;}
	private:
		bool processCollision(GameObject* operate, World& world, float dt);
		GameObject* _parentOfBullet = nullptr;
		Texture* _texture=nullptr;
		bool  _explosive = 0;
		bool  _corpseSpawned=false;
		int _damage = 0;
		float _explosiveRadius = 0;
		float _speedX = 0;
		float _speedY = 0;
		float _pushForce = 0;
		int _direction = 1;

		bool predictionCollide(Point movement, World& world, float dt);
		bool predictionCollideX(float x, World& world, float dt);
		bool predictionCollideY(float y, World& world, float dt);
};

#endif
