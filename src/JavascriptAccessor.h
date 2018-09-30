#ifndef JS_V8_ACCESSOR_H
#define JS_V8_ACCESSOR_H

#include "include/cef_v8.h"

class JavascriptAccessor :
	public CefV8Accessor{
	public:
		bool Get(
			const CefString& name,
			const CefRefPtr<CefV8Value> object,
			CefRefPtr<CefV8Value>& retval,
			CefString& exception
			);
		bool Set(
			const CefString& name,
			const CefRefPtr<CefV8Value> object,
			const CefRefPtr<CefV8Value> value,
			CefString& exception
			);
	private:
		std::string _valueString = "DEFAULT VALUE";
		IMPLEMENT_REFCOUNTING(JavascriptAccessor);
};

#endif