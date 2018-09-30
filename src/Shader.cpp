#include <iostream>
#include <fstream>
#include <sstream>
#include "Shader.h"

Shader::Shader(){
}

Shader::Shader(std::string vPath, std::string fPath){
	// assume it's loaded from a file.
	init();
	loadFromFile( vPath, fPath );
}

Shader::~Shader(){
	glDeleteShader(_vertexShader);
	glDeleteShader(_fragmentShader);
	glDeleteProgram(_shaderProgram);
}

void Shader::init(){
	_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	_vertexShader = glCreateShader(GL_VERTEX_SHADER);
	_shaderProgram = glCreateProgram();
}

void Shader::loadFromSource(const char* vertexSource, const char* fragmentSource){
	glShaderSource(_vertexShader, 1, &vertexSource, 0);
	glShaderSource(_fragmentShader, 1, &fragmentSource, 0);

	int shaderSuccess=0;
	char shaderLog[512];
	glCompileShader(_vertexShader);
	glGetShaderiv(_vertexShader, GL_COMPILE_STATUS, &shaderSuccess);
	if(shaderSuccess == 0){
		std::cout << "VSHADER ERROR\n";
		glGetShaderInfoLog(_vertexShader, 512, 0, shaderLog);
		std::cout << shaderLog << std::endl;
	}
	glCompileShader(_fragmentShader);
	glGetShaderiv(_fragmentShader, GL_COMPILE_STATUS, &shaderSuccess);
	if(shaderSuccess == 0){
		std::cout << "FSHADER ERROR\n";
		glGetShaderInfoLog(_fragmentShader, 512, 0, shaderLog);
		std::cout << shaderLog << std::endl;
	}
	std::cout << shaderLog << std::endl;
	// TODO: check for errors later on.
	glAttachShader(_shaderProgram, _vertexShader);
	glAttachShader(_shaderProgram, _fragmentShader);
	glLinkProgram(_shaderProgram);

	int success=0;
	glGetProgramiv(_shaderProgram, GL_LINK_STATUS, &success);
	char log[512];
	if(!success){
		std::cout << "Shader error" << std::endl;
		glGetProgramInfoLog(_shaderProgram, 512, 0, log);
		std::cout << log << std::endl;
	}
	// again check for errors TODO:
} 

void Shader::loadFromFile(std::string vsPath, std::string fsPath){
	std::fstream vs(vsPath), fs(fsPath);
	std::stringstream vs_ss, fs_ss;
	vs_ss << vs.rdbuf();
	fs_ss << fs.rdbuf();
	vs_ss.write("\0", 1);
	fs_ss.write("\0", 1);
	std::string vs_source = vs_ss.str(), fs_source = fs_ss.str();
	loadFromSource(vs_source.c_str(), fs_source.c_str());
}

void Shader::bind(){
	glUseProgram(_shaderProgram);
}

void Shader::unbind(){
	glUseProgram(0);
}

int Shader::getUniformLocation(const char* uniform){
	return glGetUniformLocation(_shaderProgram, uniform);
}
