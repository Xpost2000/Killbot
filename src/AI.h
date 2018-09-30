#ifndef AI_H
#define AI_H

#include "World.h"

// an "AI" object to make enemy production
// really rapid and easy. :)
class GameObject;
class AI{
	public:
		AI(GameObject* parent);
		~AI();
		virtual void update(float dt, World& world);
		GameObject* getParent() { return _parent; }
	private:
		GameObject* _parent;
};

#endif
