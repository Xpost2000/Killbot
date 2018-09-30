#ifndef BROWSERRENDERHANDLER_CEF_H
#define BROWSERRENDERHANDLER_CEF_H

#include "include/cef_app.h"
#include "include/cef_render_handler.h"
#include "Texture.h"

class BrowserRenderHandler : public CefRenderHandler
{
	public:
		BrowserRenderHandler(int w, int h);
		~BrowserRenderHandler();
		bool GetViewRect(CefRefPtr<CefBrowser> browser, CefRect& rect);
		void OnPaint(CefRefPtr<CefBrowser> browser,
			PaintElementType type,
			const RectList& dirtyRects,
			const void* buffer,
			int width,
			int height);

		Texture* getTexture() { return _texture; }
	private:
		unsigned char* asBytes = nullptr;
		Texture* _texture = nullptr;
		int _w = 0, _h = 0;

		IMPLEMENT_REFCOUNTING(BrowserRenderHandler);
};

#endif