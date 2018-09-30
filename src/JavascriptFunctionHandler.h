#ifndef JS_V8_HANDLER_H
#define JS_V8_HANDLER_H
#include "include/cef_v8.h"
#include <functional>
#include <map>

typedef CefRefPtr<CefV8Value> JSReturnType;
typedef std::function< JSReturnType (CefRefPtr<CefV8Value> obj, const CefV8ValueList& args, CefString& exception) > JSCallbackFunc;

// just carry an std::map of
// functions with matching names I guess.
// for now to test integration just hardcode it.
class JavascriptFunctionHandler :
	public CefV8Handler{
	public:
		bool Execute(
			const CefString& name,
			CefRefPtr<CefV8Value> object,
			const CefV8ValueList& arguments,
			CefRefPtr<CefV8Value>& retval,
			CefString& exception
			);
		void addFunction(std::string name, JSCallbackFunc);
		void RegisterToObject(std::string registerAs, CefRefPtr<CefV8Value>& object);
		CefRefPtr<CefV8Value>& getFunctionObject(std::string name);
	private:
		std::map<std::string, JSCallbackFunc> _nativeCallbacks;
		std::map<std::string, JSReturnType> _functionObjects;
		IMPLEMENT_REFCOUNTING(JavascriptFunctionHandler);
};

#endif