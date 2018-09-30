#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "AI.h"

#include "Point.h"
#include "Renderer2D.h"
#include "Texture.h"

// the game objects are really
// player
// enemies and other enemy types
// and bullets
class World;
class GameObject{
	public:
		GameObject();
		GameObject(Point pos, Point size, Texture* texture = nullptr, AI* aiPtr=nullptr);
		GameObject(const GameObject& other) = default;
		//GameObject(const GameObject&& other) = default;
		~GameObject();

		void init(Point pos, Point size, Texture* texture = nullptr, AI* aiPtr = nullptr);
		void setHealth(int health) { _hp = health; }
		void setMaxHealth(int maxHealth) { _maxHp = maxHealth; }
		void setTexture(Texture* tex);
		void setAI(AI* aiPtr);

		void update(float dt, World& world);
		void draw(Renderer2D* renderer);

		Point &getPosition(){ return _position; }
		Point &getHitBoxPos() { return hitBoxPos; }
		Point &getHitBoxSize() { return hitBoxSize; }
		Point &getVelocity(){ return _velocity; }
		Point &getSize(){ return _size; }

		AI* getAI() { return _ai; }

		int &getHealth() { return _hp; }
		int &getMaxHealth() { return _maxHp; }

		bool collide(GameObject& other){
			return (hitBoxPos.x < other.hitBoxPos.x + other.hitBoxSize.x && hitBoxPos.x + hitBoxSize.x > other.hitBoxPos.x)&&
			(hitBoxPos.y < other.hitBoxPos.y + other.hitBoxSize.y && hitBoxPos.y + hitBoxSize.y > other.hitBoxPos.y);
		}

		void setHitBox(Point hitBoxPos, Point hitPoxSize);
		int getType(){ return _magicNumberType; }
		int getKillbotType() { return _killBotType; }

		bool flipX = false;
		bool gravityEnabled = true;
		bool collidable = false;
		bool deletable = false;
		bool drawable = true;

		void flash() { _flashTimer = 0.10; } // this helps SO MUCH
	private:
		float _flashTimer = 0; // in seconds
		friend class GameObjectFactory;
		int _magicNumberType = -1;
		int _killBotType = 0; // TODO: If enemy.
		int _hp = 1; // so no instant deletion.
		int _maxHp = 1;

		Point hitBoxPos, hitBoxSize;

		Texture* _spriteTexture = nullptr;
		AI* _ai = nullptr;

		Point _position, _size;
		Point _velocity;
};

#endif
