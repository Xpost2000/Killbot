#include "FontRenderer.h"
#include <GL/glew.h>

FontRenderer::FontRenderer(){
}	

void FontRenderer::init(){
	FT_Init_FreeType( &m_ft );
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	// This is setting up stuff just in case has issues with no initialization on drawing the text.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_2D, 0);

	glGenBuffers(1, &vbo);
	glGenVertexArrays(1, &vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindVertexArray( vao );
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(0, 2, GL_FLOAT, false, sizeof(float) * 8, 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(float) * 8, (void*)(sizeof(float)*2));
	glVertexAttribPointer(2, 4, GL_FLOAT, false, sizeof(float) * 8, (void*)(sizeof(float)*4));
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);


}

FontRenderer::~FontRenderer(){
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);
	glDeleteTextures(1, &textureId);
	for(auto& face : m_faces){
		FT_Done_Face( face );
	}
	FT_Done_FreeType( m_ft );
}

void FontRenderer::addFont( std::string path, std::string font_name ){
	FT_Face _blank;
	m_indices[font_name] = m_faces.size(); // this is acceptable because size is the non zero indexed amount of elements.
	m_faces.push_back(_blank);
	FT_New_Face( m_ft, path.c_str(), 0, &m_faces.back() );
}		

// I realize this is sort of stupidly inefficient.
// I refill the texture with a different image each frame but on modern pcs it should be fine. Like mine.
void FontRenderer::renderText( float x, float y, std::string text, std::string font_name, float r, float g, float b, float a ){
	FT_Face& cur = m_faces[m_indices[font_name]];
	FT_Set_Pixel_Sizes(cur, 0, size);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindVertexArray(vao);

	glBindTexture(GL_TEXTURE_2D, textureId);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // for non power of two textures that freetype generates.

	// this is to fix the height for characters
	FT_Load_Char( cur, 'H', FT_LOAD_RENDER );
	float hBearing = cur->glyph->bitmap_top;
	for( unsigned char i : text ){
		FT_Load_Char( cur, i, FT_LOAD_RENDER );
		// font character positions.
		float fx = x + cur->glyph->bitmap_left;
		float fy = y + hBearing-cur->glyph->bitmap_top;
		float w  = cur->glyph->bitmap.width;
		float h  = cur->glyph->bitmap.rows;
		glTexImage2D(
				GL_TEXTURE_2D,
				0,
				GL_RED,
				cur->glyph->bitmap.width,
				cur->glyph->bitmap.rows,
				0,
				GL_RED,
				GL_UNSIGNED_BYTE,
				cur->glyph->bitmap.buffer
			    );
		float data[]={
			fx,   fy,   0, 0, r, g, b, a,
			fx,   fy+h, 0, 1, r, g, b, a,
			fx+w, fy,   1, 0, r, g, b, a,

			fx+w, fy,   1, 0, r, g, b, a,
			fx,   fy+h, 0, 1, r, g, b, a,
			fx+w, fy+h, 1, 1, r, g, b, a
		};
		glBufferData(
				GL_ARRAY_BUFFER,
				sizeof data,
				data,
				GL_DYNAMIC_DRAW
		);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		x+= (cur->glyph->advance.x>>6);
	}
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
}
