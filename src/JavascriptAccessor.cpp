#include "JavascriptAccessor.h"

bool JavascriptAccessor::Get(
	const CefString& name,
	const CefRefPtr<CefV8Value> object,
	CefRefPtr<CefV8Value>& retval,
	CefString& exception
	){
	return true;
}

bool JavascriptAccessor::Set(
	const CefString& name,
	const CefRefPtr<CefV8Value> object,
	const CefRefPtr<CefV8Value> value,
	CefString& exception
	){
	return true;
}