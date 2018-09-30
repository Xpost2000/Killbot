#include "GameObject.h"
#include "World.h"
#include <cstdio>

GameObject::GameObject(){
}

GameObject::GameObject(Point pos, Point size, Texture* texture, AI* aiPtr) : _position(pos), _size(size), _spriteTexture(texture), _ai(aiPtr){
	setHitBox(_position, _size);
	_velocity.x = 0;
	_velocity.y = 0;
}


GameObject::~GameObject(){

}

void GameObject::init(Point pos, Point size, Texture* tex, AI* aiPtr){
	_position = pos;
	_size = size;
	_spriteTexture = tex;
	_ai = aiPtr;
}

void GameObject::update(float dt, World& world){
	if(_ai != nullptr){
		_ai->update(dt, world);
		if (_flashTimer > 0){
			_flashTimer -= dt;
		}
	}else{
	}
}

void GameObject::draw(Renderer2D* renderer){
	if(_spriteTexture && drawable){
		Color color = { 255, 255, 255, 255 };
		if (_flashTimer > 0){
			color.r = 255;
			color.g = 0;
			color.b = 0;
			color.a = 255;
		}
		renderer->RenderRectangle(_spriteTexture, _position, _size, UV{0, 0, 1* flipX ? -1 : 1, 1}, color);
		//renderer->RenderRectangle(hitBoxPos, hitBoxSize, Color{ 255, 0, 0, 255 });
	}
}

void GameObject::setTexture(Texture* tex){
	_spriteTexture = tex;
}

void GameObject::setAI(AI* aiPtr){
	_ai = aiPtr;
}

void GameObject::setHitBox(Point pos, Point size){
	hitBoxPos = pos;
	hitBoxSize = size;
}
