#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>
#include <inttypes.h>

class Texture{
	public:
		Texture();
		Texture(const char* imagePath);
		Texture(const void* pixels);
		~Texture();

		GLuint get() { return _textureId; }

		void init(const char* imagePath);
		void init(int w, int h, unsigned char* pixels);
		void setData(int w, int h, unsigned char* pixels);
		void bind() { glBindTexture(GL_TEXTURE_2D, _textureId); }
		void unbind() { glBindTexture(GL_TEXTURE_2D, 0); }
	private:
		uint8_t* _bytes;
		GLuint _textureId;
};

#endif
