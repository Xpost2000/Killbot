#include "BrowserRenderHandler.h"
#include <cstdlib>

BrowserRenderHandler::BrowserRenderHandler(int w, int h) : _w(w), _h(h){
	_texture = new Texture();
	_texture->init(w, h, 0);
	asBytes = new unsigned char[w*h*4];
}

BrowserRenderHandler::~BrowserRenderHandler(){
	delete _texture;
	delete asBytes;
}

bool BrowserRenderHandler::GetViewRect(CefRefPtr<CefBrowser> browser, CefRect& rect){
	rect = CefRect(0, 0, _w, _h);

	return true;
}

void BrowserRenderHandler::OnPaint(CefRefPtr<CefBrowser> browser,
	PaintElementType type,
	const RectList& dirtyRects,
	const void* buffer,
	int width,
	int height){
	_w = width;
	_h = height;
	memcpy(asBytes, buffer, width*height * 4);
	//printf("asBytes[0] : %d, asBytes[1] : %d, asBytes[2] : %d, asBytes[3] : %d\n", asBytes[0], asBytes[1], asBytes[2], asBytes[3]);
	_texture->bind();
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _w, _h, 0, GL_BGRA, GL_UNSIGNED_BYTE, asBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // I need a pixelated look so nearest filtering.
	glGenerateMipmap(GL_TEXTURE_2D);
}