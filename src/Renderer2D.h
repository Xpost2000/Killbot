#ifndef RENDERER2D_H
#define RENDERER2D_H

#include <GL/glew.h>

#include "Animation.h"
#include "RectangleRenderer.h"
#include "SpritebatchRenderer.h"
#include "FontRenderer.h"
#include "Shader.h"

// this will hold a sprite batcher
// and particle renderer to render
// all our 2D stuff.

// this class just holds other renderers that actually render
// this is more like a master class.
enum BlendMode{
	AlphaBlending,
	AdditiveBlending
};

class Renderer2D{
	public:
		Renderer2D(int w, int h);
		Renderer2D(){};
		~Renderer2D();

		void Clear(float r, float g, float b, float a);

		void BlendingMode( BlendMode blendMode );
		void ScreenShake( float timeInSeconds, float strengthX, float strengthY );

		void init(int w, int h);
		void update(float dt);
		void RenderRectangle(Point pos, Point size, Color color);
		void RenderRectangle(Texture* texture, Point pos, Point size, UV uvs, Color color);
		void RenderRectangle(Animation animation, Point pos, Point size, UV uvs, Color color);
		void RenderRectangle(Animation animation, Point pos, Point size, Color color);

		void SpritebatchBegin(Texture* texture);
		void SpritebatchDraw(Point pos, Point size, Color color, UV uvs = UV{0, 0, 1, 1});
		void SpritebatchEnd();

		void AddFont( std::string path, std::string font_name ) { _fontRenderer.addFont(path, font_name); }
		inline void SetFontSize( int sz ) { _fontRenderer.setSize(sz); }
		void RenderText( Point position, std::string text, std::string font_name, Color color, int size = 12 ) { _textShader.bind(); _fontRenderer.setSize(size); _fontRenderer.renderText( position.x, position.y, text, font_name, color.r, color.g, color.b, color.a ); _textShader.unbind(); }
	
		// the virtual width and height. That's how it renders so this should technically be fine.
		int getWidth() { return 1024; }
		int getHeight() { return 768; }
		int getPhysicalWidth() { return _w; }
		int getPhysicalHeight() { return _h; }
		//void RenderRectangle(int textureId, Point pos, Point size, Color color);
	private:
		float _shakeTime = 0;
		float _shakeX=0, _shakeY=0;
		int _w, _h;
		//TODO: Allow passing in shader types instead from like a shader manager.
		Shader _defaultShader, _textureShader, _textShader; // load from source
		RectangleRenderer _rectRend; // a simple inefficient renderer for testing
		SpritebatchRenderer _spriteBatcher; // a more efficient spritebatcher
		FontRenderer _fontRenderer;
};

#endif
