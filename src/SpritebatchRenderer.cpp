#include "SpritebatchRenderer.h"

SpritebatchRenderer::SpritebatchRenderer(){
}

SpritebatchRenderer::~SpritebatchRenderer(){
	glDeleteVertexArrays(1, &_vertexArray);
	glDeleteBuffers(1, &_vertexBuffer);
}

void SpritebatchRenderer::init(){
	glGenBuffers(1, &_vertexBuffer);
	glGenVertexArrays(1, &_vertexArray);

	glBindVertexArray(_vertexArray);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);

	glEnableVertexAttribArray(0); // Positions
	glEnableVertexAttribArray(1); // UVS 
	glEnableVertexAttribArray(2); // Colors

	glVertexAttribPointer(0, 2, GL_FLOAT, false, sizeof (float) * 8, 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof (float) * 8, (void*)(sizeof(float)*2));
	glVertexAttribPointer(2, 4, GL_FLOAT, false, sizeof (float) * 8, (void*)(sizeof(float)*4));

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void SpritebatchRenderer::Begin(Texture* texture){
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
	glBindTexture(GL_TEXTURE_2D, texture->get());
	glBindVertexArray(_vertexArray);
}

void SpritebatchRenderer::Draw(Point pos, Point size, Color color, UV uvs){
	float vertices[]={
		pos.x, pos.y, uvs.u, uvs.v, color.r, color.g, color.b, color.a,
		pos.x, pos.y+size.y, uvs.u, uvs.h, color.r, color.g, color.b, color.a,
		pos.x+size.x, pos.y+size.y, uvs.w, uvs.h, color.r, color.g, color.b, color.a,
		pos.x+size.x, pos.y+size.y, uvs.w, uvs.h, color.r, color.g, color.b, color.a,
		pos.x, pos.y, uvs.u, uvs.v, color.r, color.g, color.b, color.a,
		pos.x+size.x, pos.y, uvs.w, uvs.u, color.r, color.g, color.b, color.a
	};
	// 48 floats cause 8 floats per vertex
	for(int i = 0; i < 8*6; ++i){
		_verticesData.push_back(vertices[i]);
	}
}

void SpritebatchRenderer::End(){
	_DrawContents();
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void SpritebatchRenderer::_DrawContents(){
	glBufferData(GL_ARRAY_BUFFER, _verticesData.size(), &_verticesData[0], GL_STATIC_DRAW);
	glDrawArrays(GL_TRIANGLES, 0, _verticesData.size());
	_verticesData.clear();
}
