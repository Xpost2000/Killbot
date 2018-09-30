#include "Command.h"
#include "AI.h"

Command::Command(AI* _aiParent) : _parent(_aiParent){
}

Command::~Command(){
}
