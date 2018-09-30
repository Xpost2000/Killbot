#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "deps/stb_image.h"

Texture::Texture(){

}

Texture::Texture(const char* imagePath){
	init(imagePath);
}

Texture::Texture(const void* pixels){

}

Texture::~Texture(){
	glDeleteTextures(1, &_textureId);
}

void Texture::init(int w, int h, unsigned char* pixels){
	glGenTextures(1, &_textureId);
	bind();
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // I need a pixelated look so nearest filtering.
	glGenerateMipmap(GL_TEXTURE_2D);
	unbind();
}

void Texture::init(const char* imagePath){
	glGenTextures(1, &_textureId);
	int imageWidth, imageHeight, components;
	_bytes = stbi_load(imagePath, &imageWidth, &imageHeight, &components, 4); 
	bind();
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, _bytes);	
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST ); // I need a pixelated look so nearest filtering.
		glGenerateMipmap(GL_TEXTURE_2D);
	unbind();
	stbi_image_free(_bytes);
}

void Texture::setData(int w, int h, unsigned char* pixels){
	bind();
	//MARKER
	glTexImage2D(GL_TEXTURE_2D, 0, GL_BGRA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
}
