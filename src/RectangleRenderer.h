#ifndef RECT_RENDERER_H
#define RECT_RENDERER_H

#include <GL/glew.h>
#include "Point.h"
#include "Color.h"
#include "Texture.h"

/*
 * Slow simple rectangle renderer.
 */
class RectangleRenderer{
	public:
		RectangleRenderer();
		~RectangleRenderer();

		void DrawRectangle(Point pos, Point size, Color color);
		void init();
		// TODO:
		void DrawRectangle(Texture* texture, Point pos, Point size, UV uvs, Color color);
	private:
		GLuint _vertexBuffer=0, _vertexArray=0;
};

#endif
