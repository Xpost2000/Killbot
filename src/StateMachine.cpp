#include "StateMachine.h"
#include "State.h"

StateMachine::StateMachine(){
}

StateMachine::~StateMachine(){
	for(auto& st : _states){
		delete st.second;
	}
}


State* StateMachine::addState( std::string name, State* ptr ){
	if(!_states.count(name)){
		_states.emplace( name, ptr );
		_states[name]->_parent = this;
		return _states[name];
	}else{
		return _states[name];
	}
}

void StateMachine::setCurrent( std::string name ){
	if(_states.count(name)){
		if(_current != nullptr){ _current->OnExit(); }
		_current = _states[name];
		_current->OnEnter();
	}
}

void StateMachine::update(float dt){
	if(_current)
		_current->update(dt);
}

void StateMachine::draw(Renderer2D* renderer){
	if(_current)
		_current->draw(renderer);
}
