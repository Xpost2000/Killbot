#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <GL/glew.h>

class Shader{
	public:
		Shader();
		Shader(std::string vertexShaderPath, std::string fragmentShaderPath);
		~Shader();

		void init();

		void loadFromSource(const char* vertexSource, const char* fragmentSource);
		void loadFromFile(std::string vsPath, std::string fsPath);

		void bind();
		void unbind();

		int getUniformLocation(const char* uniform);
	private:
		GLuint _vertexShader=0, _fragmentShader=0;
		GLuint _shaderProgram=0;
};

#endif
