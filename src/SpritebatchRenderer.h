#ifndef SPRITEBATCHER_H
#include <GL/glew.h>
#include <vector>

#include "Texture.h"
#include "Color.h"
#include "Point.h"

class SpritebatchRenderer{
	public:
		SpritebatchRenderer();
		~SpritebatchRenderer();

		void init();

		void Begin(Texture* texture);
		void Draw(Point pos, Point size, Color color, UV uvs = UV{0, 0, 1, 1});
		void End(); // aka draw
	private:
		void _DrawContents();

		GLuint _vertexArray, _vertexBuffer;
		std::vector<float> _verticesData;
};
#endif
