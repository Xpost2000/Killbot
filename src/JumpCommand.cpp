#include "JumpCommand.h"
#include "SoundManager.h"
#include "constants.h"

JumpCommand::JumpCommand(AI* _aiParent, float height, float maxHeight) : Command(_aiParent), _height(height), _maxHeight(maxHeight){
}

JumpCommand::~JumpCommand(){
}
		
void JumpCommand::update(float dt, World& world){
	GameObject* parent = getParent()->getParent();
	if(_jumpCount < _maxJumps){
		SoundManager::instance()->playSound( "audio/fx/jump.wav" );
		parent->getVelocity().y = _height;
		_jumpCount++;
	}
}
