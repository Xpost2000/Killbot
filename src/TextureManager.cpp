#include "TextureManager.h"
#include <cstdio>
TextureManager* TextureManager::_instance = nullptr;	

TextureManager::TextureManager(){
}

TextureManager::~TextureManager(){
	for(auto & texture : _textures){
		delete texture.second;
	}
}

Texture* TextureManager::addTexture(std::string path){
	if(!_textures.count(path)){
		Texture* result = new Texture();
		result->init(path.c_str());
		_textures.emplace(path, result);
		printf("Added new texture : %s\n", path.c_str());
		return result;
	}else{
		printf("%s already exists as a texture.\n", path.c_str());
		return _textures[path];
	}
}

Texture* TextureManager::getTexture(std::string path){
	Texture* result = nullptr;
	if(!_textures.count(path)){
		result = addTexture(path);
	}else{
		result = _textures[path];
	}
	return result;
}
