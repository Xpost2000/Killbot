#include "AI.h"
#include "GameObject.h"

AI::AI(GameObject* parent) : _parent(parent){
}

AI::~AI(){
}

void AI::update(float dt, World& world){
}
