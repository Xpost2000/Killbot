#ifndef CEFMANAGER_H
#define CEFMANAGER_H

#include "BrowserClient.h"
#include "BrowserRenderHandler.h"

/*
Someone please tell me why this is like my best solution to this?
I think there's a better way to do it but I don't know what it is...
So more singletons to the rescue :|

This class is kind of like a CefApp
but not exactly.

It's really a giant singleton that 
contains all objects related to Cef (On the main program thread)
*/

class CefManager{
	public:
		CefManager();
		~CefManager();

		static CefManager* instance(){
			if (_instance == nullptr) _instance = new CefManager();
			return _instance;
		}

		void InitBrowser(int w, int h, std::string url);

		int InitializeCEF(int argc, char** argv);
		void ShutdownCEF();
		void ShutdownBrowser();
		
		CefRefPtr<CefBrowser> GetCefBrowser(){ return _cefBrowser; }
		CefRefPtr<BrowserClient> GetBrowserClient(){ return _browserClient; }
		CefRefPtr<BrowserRenderHandler> GetRenderHandler() { return _renderHandler; }

		CefMainArgs& getMainArgs() { return _mainArgs; }
		CefSettings& getSettings() { return _settings; }
	private:
		CefRefPtr<CefBrowser> _cefBrowser = nullptr;
		CefRefPtr<BrowserClient> _browserClient = nullptr;
		CefRefPtr<BrowserRenderHandler> _renderHandler = nullptr;

		CefMainArgs _mainArgs;
		CefSettings _settings;
		static CefManager* _instance;
};

#endif