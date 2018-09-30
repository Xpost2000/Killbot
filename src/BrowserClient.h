#ifndef BROWSERCLIENT_CEF_H
#define BROWSERCLIENT_CEF_H
#include "include/cef_app.h"
#include "include/cef_client.h"
#include "include/cef_render_handler.h"
#include "include/cef_life_span_handler.h"
#include "include/cef_load_handler.h"
#include "wrapper/cef_helpers.h"
#include "BrowserRenderHandler.h"

class BrowserClient :
	public CefClient,
	public CefLifeSpanHandler,
	public CefLoadHandler
{
	public:
		BrowserClient(CefRefPtr<CefRenderHandler> renderHandler);
		~BrowserClient();
		virtual CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler();
		virtual CefRefPtr<CefLoadHandler> GetLoadHandler();
		virtual CefRefPtr<CefRenderHandler> GetRenderHandler();
		// CefLifeSpanHandler methods.
		void OnAfterCreated(CefRefPtr<CefBrowser> browser);
		bool DoClose(CefRefPtr<CefBrowser> browser);
		void OnBeforeClose(CefRefPtr<CefBrowser> browser);
		void OnLoadEnd(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, int httpStatusCode);
		bool OnLoadError(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefLoadHandler::ErrorCode errorCode, const CefString & failedUrl, CefString & errorText);
		void OnLoadingStateChange(CefRefPtr<CefBrowser> browser, bool isLoading, bool canGoBack, bool canGoForward);
		void OnLoadStart(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame);
		bool closeAllowed() const;
		bool isLoaded() const;

		bool OnProcessMessageReceived(
			CefRefPtr<CefBrowser> browser,
			CefProcessId source_process,
			CefRefPtr<CefProcessMessage> message
			);
	private:
		int browser_id;
		bool closing = false;
		bool loaded = false;
		CefRefPtr<CefRenderHandler> _renderHandler;
		IMPLEMENT_REFCOUNTING(BrowserClient);
};

#endif