#include "Renderer2D.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "RandomNumberGenerator.h"

Renderer2D::Renderer2D(int w, int h){
	init(w, h);
}

Renderer2D::~Renderer2D(){
}

void Renderer2D::ScreenShake(float timeInSeconds, float strengthX, float strengthY){
	_shakeTime = timeInSeconds;
	_shakeX = strengthX;
	_shakeY = strengthY;
}

void Renderer2D::init(int w, int h){
	// setup a matrix here
	// and shader 
	glEnable(GL_BLEND);
	_rectRend.init();
	_fontRenderer.init();
	_spriteBatcher.init();
	_defaultShader.init();
	_textureShader.init();
	_textShader.init();
	_defaultShader.loadFromFile("shaders/default.vs", "shaders/default.fs");
	_textureShader.loadFromFile("shaders/default.vs", "shaders/textured.fs");
	_textShader.loadFromFile("shaders/default.vs", "shaders/text.fs");

	int virtualScreenWidth = 1024;
	int virtualScreenHeight = 768;
	_w = w;
	_h = h;
	// this needs to me column major.
	glm::mat4 proj = glm::ortho(0.0f, (float)virtualScreenWidth, (float)virtualScreenHeight, 0.0f, -1.f, 1.f);

	_defaultShader.bind();
	glUniformMatrix4fv( _defaultShader.getUniformLocation("orthographicMatrix"), 1, false, glm::value_ptr(proj) );
	_defaultShader.unbind();

	_textureShader.bind();
	glUniformMatrix4fv( _textureShader.getUniformLocation("orthographicMatrix"), 1, false, glm::value_ptr(proj) );
	_textureShader.unbind();

	_textShader.bind();
	glUniformMatrix4fv( _textShader.getUniformLocation("orthographicMatrix"), 1, false, glm::value_ptr(proj) );
	_textShader.unbind();

}

// note I emphasize a difference between DrawRectangle and Render.
void Renderer2D::RenderRectangle(Point pos, Point size, Color color){
	_defaultShader.bind();
	_rectRend.DrawRectangle(pos, size, color);
	_defaultShader.unbind();
}

void Renderer2D::RenderRectangle(Texture* texture, Point pos, Point size, UV uvs, Color color){
	
	_textureShader.bind();
	if (_shakeTime > 0){
		glUniform2f(_textureShader.getUniformLocation("cameraPos"), RandomFloat(-_shakeX, _shakeX).get(), RandomFloat(-_shakeY, _shakeY).get());
	}
	glUniform1i(_textureShader.getUniformLocation("texture"), 0);
	glActiveTexture(GL_TEXTURE0);
	_rectRend.DrawRectangle(texture, pos, size, uvs, color);
	_textureShader.unbind();
}

void Renderer2D::update(float dt){
	if (_shakeTime > 0){
		_shakeTime -= dt;
	}
}

void Renderer2D::RenderRectangle(Animation animation, Point pos, Point size, Color color){
	if(animation.getCurrentFrame()->getTexture() == nullptr){
		printf("Animation Frame has no texture?\n");
	}
	RenderRectangle(animation.getCurrentFrame()->getTexture(), pos, size, animation.getCurrentFrame()->getUvs(), color);
}

void Renderer2D::RenderRectangle(Animation animation, Point pos, Point size, UV uvs, Color color){
	if(animation.getCurrentFrame()->getTexture() == nullptr){
		printf("Animation Frame has no texture?\n");
	}
	RenderRectangle(animation.getCurrentFrame()->getTexture(), pos, size, uvs, color);
}

void Renderer2D::SpritebatchBegin(Texture* texture){
	_textureShader.bind();
	glUniform1i(_textureShader.getUniformLocation("texture"), 0);
	glActiveTexture(GL_TEXTURE0);
	_spriteBatcher.Begin(texture);
}

void Renderer2D::SpritebatchDraw(Point pos, Point size, Color color, UV uvs){
	_spriteBatcher.Draw(pos, size, color, uvs);
}

void Renderer2D::SpritebatchEnd(){
	_spriteBatcher.End();
	_textureShader.unbind();
}

void Renderer2D::Clear(float r, float g, float b, float a){
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(r, g, b, a);
	glViewport(0, 0, _w, _h);
}

void Renderer2D::BlendingMode( BlendMode blendMode ){
	switch(blendMode){
		case BlendMode::AlphaBlending:
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			break;
		case AdditiveBlending:
			glBlendFunc(GL_SRC_ALPHA, GL_ONE);
			break;
	}
}
