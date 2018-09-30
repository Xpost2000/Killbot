#include "RectangleRenderer.h"

RectangleRenderer::RectangleRenderer(){

}

void RectangleRenderer::init(){
	glGenBuffers(1, &_vertexBuffer);
	glGenVertexArrays(1, &_vertexArray);

	glBindVertexArray(_vertexArray);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);

//	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*6, 0, GL_DYNAMIC_DRAW);
//	just keep reconstructing it for now. It's easier
	glEnableVertexAttribArray(0); // Positions
	glEnableVertexAttribArray(1); // UVS 
	glEnableVertexAttribArray(2); // Colors

	glVertexAttribPointer(0, 2, GL_FLOAT, false, sizeof (float) * 8, 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof (float) * 8, (void*)(sizeof(float)*2));
	glVertexAttribPointer(2, 4, GL_FLOAT, false, sizeof (float) * 8, (void*)(sizeof(float)*4));

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

RectangleRenderer::~RectangleRenderer(){
	glDeleteVertexArrays(1, &_vertexArray);
	glDeleteBuffers(1, &_vertexBuffer);
}

void RectangleRenderer::DrawRectangle(Point pos, Point size, Color color){
	float vertices[]={
		pos.x, pos.y, 0, 0, color.r, color.g, color.b, color.a,
		pos.x, pos.y+size.y, 0, 1, color.r, color.g, color.b, color.a,
		pos.x+size.x, pos.y+size.y, 1, 1, color.r, color.g, color.b, color.a,
		pos.x+size.x, pos.y+size.y, 1, 1, color.r, color.g, color.b, color.a,
		pos.x, pos.y, 0, 0, color.r, color.g, color.b, color.a,
		pos.x+size.x, pos.y, 1, 0, color.r, color.g, color.b, color.a
	};
	glBindVertexArray(_vertexArray);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}


void RectangleRenderer::DrawRectangle(Texture* texture, Point pos, Point size, UV uvs, Color color){
	float vertices[]={
		pos.x, pos.y, uvs.u, uvs.v, color.r, color.g, color.b, color.a,
		pos.x, pos.y+size.y, uvs.u, uvs.h, color.r, color.g, color.b, color.a,
		pos.x+size.x, pos.y+size.y, uvs.w, uvs.h, color.r, color.g, color.b, color.a,
		pos.x+size.x, pos.y+size.y, uvs.w, uvs.h, color.r, color.g, color.b, color.a,
		pos.x, pos.y, uvs.u, uvs.v, color.r, color.g, color.b, color.a,
		pos.x+size.x, pos.y, uvs.w, uvs.u, color.r, color.g, color.b, color.a
	};
	glBindVertexArray(_vertexArray);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

	texture->bind();
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	texture->unbind();
}
