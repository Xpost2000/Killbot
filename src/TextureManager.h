#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <map>
#include "Texture.h"

class TextureManager{
	public:
		TextureManager();
		~TextureManager();
		static TextureManager* instance(){
			if(_instance == nullptr) _instance = new TextureManager();
			return _instance;
		}

		Texture* addTexture(std::string path);
		Texture* getTexture(std::string path);
	private:
		std::map<std::string, Texture*> _textures;
		static TextureManager* _instance;	
};

#endif
