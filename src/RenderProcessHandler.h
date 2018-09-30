#ifndef RENDER_PROCESS_HANDLER_H
#define RENDER_PROCESS_HANDLER_H

#include "include/cef_app.h"
#include "include/cef_browser.h"
#include "include/cef_render_process_handler.h"

#include <SDL2/SDL.h>

#include "JavascriptAccessor.h"
#include "JavascriptFunctionHandler.h"

class RenderProcessApplication : public CefApp,
				 public CefRenderProcessHandler{
	public:
		RenderProcessApplication();
		~RenderProcessApplication();

		virtual CefRefPtr<CefRenderProcessHandler> GetRenderProcessHandler() { return this; }

		void OnRenderThreadCreated(CefRefPtr<CefListValue> extra_info);
		void OnWebKitInitialized();
		void OnBrowserCreatesd(CefRefPtr<CefBrowser> browser);
		void OnBrowserDestroyed(CefRefPtr<CefBrowser> browser);

		CefRefPtr<CefLoadHandler> GetLoadHandler() { return NULL; }

		/*
		 * So CEF provides interfaces for me to basically provide an implementation for.
		 * Basically it's like....
		 *
		 * Telling someone to do something, without really caring how they do it.
		 *
		 * For example
		 *
		 * Tell a person to kill someone.
		 *
		 * To kill some one you must,
		 *
		 * - Find the person
		 * - Make sure the person can't possibly be alive.
		 *
		 * in code it's probably like
		 *
		 * abstract function IsPersonDead();
		 * abstract function HowDoIMakeSurePersonIsDead();
		 * abstract function KillPerson();
		 *
		 * now let's have a few implementations
		 *
		 * so for stealth...
		 *
		 * StealthKill{
		 * 	KillPerson(){
		 * 		UseKnife to kill person;
		 * 	}
		 *
		 *	HowDoIMakeSurePersonIsDead(){
		 *		Check pulse, inject poison for good measure.
		 *	}
		 * }
		 *
		 * NonStealthKill{
		 * 	KillPerson(){
		 * 		Use Gun to kill person ( preferably unsilenced. );
		 * 	}
		 *
		 * 	HowDoIMakeSurePersonIsDead(){
		 * 		Check pulse OR keep shooting to make sure.
		 * 	}
		 * }
		 */

		/*
		 * So CEF requires me to implement these functions for a renderer process.
		 *
		 * OnContextCreated,
		 * OnContextReleased,
		 * and a few other important ones...
		 *
		 * We'll focus on 
		 *
		 * OnContextCreated and OnProcessMessageReceived.
		 */

		virtual void OnContextCreated(CefRefPtr<CefBrowser> browser,
			CefRefPtr<CefFrame> frame,
			CefRefPtr<CefV8Context> context);
		virtual void OnContextReleased(CefRefPtr<CefBrowser> browser,
			CefRefPtr<CefFrame> frame,
			CefRefPtr<CefV8Context> context);
		void OnFocusedNodeChanged(CefRefPtr<CefBrowser> browser,
			CefRefPtr<CefFrame> frame,
			CefRefPtr<CefDOMNode> node);
		bool OnProcessMessageReceived(CefRefPtr<CefBrowser> browser,
			CefProcessId source_process,
			CefRefPtr<CefProcessMessage> message);
	private:
		std::string _txtBarMessage = "";

		bool _didWeReceiveAMessage = false;

		bool _canWeFightBoss = false;
		bool _isThereABoss = false;
		int  _playerMaxHealth = 0, _currentPlayerHealth = 0;
		int  _bossMaxHealth = 0, _currentBossHealth = 0;

		int _currentGameScore = 0;
		int _playerLives = 0;

		int _currentGameRound = 0;
		int _currentBulletIndex = 0;
		int _currentBulletCount = 0;
		int _BulletCounts[5];

		std::vector<SDL_DisplayMode> displayModes;

		CefRefPtr<JavascriptAccessor> accessor;// = new JavascriptAccessor;
		CefRefPtr<JavascriptFunctionHandler> jsHandler;// = new JavascriptFunctionHandler;
		void CreateNativeFunctions(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefV8Context> context);
		void RegisterNativeFunctions(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefV8Context> context);
		IMPLEMENT_REFCOUNTING(RenderProcessApplication);
};

#endif
