#include "JavascriptFunctionHandler.h"

bool JavascriptFunctionHandler::Execute
	(
	const CefString& name,
	CefRefPtr<CefV8Value> object,
	const CefV8ValueList& arguments,
	CefRefPtr<CefV8Value>& retval,
	CefString& exception
	){
	for (auto& callback : _nativeCallbacks){
		if (callback.first == std::string(name)){ // I check the names over here.
			retval = callback.second(object, arguments, exception);
		//	MessageBox(NULL, name.ToString().c_str(), "Called native function from Javascript Callback", MB_ICONEXCLAMATION);
			return true;
		}
	}
	return false;
}

void JavascriptFunctionHandler::RegisterToObject(std::string registerAs, CefRefPtr<CefV8Value>& object){
	object->SetValue(registerAs, _functionObjects[registerAs], V8_PROPERTY_ATTRIBUTE_NONE);
}

void JavascriptFunctionHandler::addFunction(std::string name, JSCallbackFunc function){
	_nativeCallbacks.emplace(name, function);
	_functionObjects.emplace(name, CefV8Value::CreateFunction(name, this));
	std::printf("Registered native function : %s\n", name.c_str());
}

CefRefPtr<CefV8Value>& JavascriptFunctionHandler::getFunctionObject(std::string name){
	return _functionObjects[name];
}
