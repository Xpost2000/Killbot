#include "SoundManager.h"
#include <cstdio>
SoundManager* SoundManager::_instance = nullptr;

SoundManager::SoundManager(){

}

SoundManager::~SoundManager(){
	for(auto& snd : _sounds){
		Mix_FreeChunk(snd.second);
	}
	for(auto& mus : _musics){
		Mix_FreeMusic(mus.second);
	}
}

void SoundManager::addMusic( std::string path ){
	/*
	if(!_musics.count(path)){
		Mix_Music* music = Mix_LoadMUS( path.c_str() );
		if(music == nullptr){
			printf("Music Load Failure : %s\n", Mix_GetError());
		}
		_musics.emplace(path, music);
	}
	*/
	addSound(path);
}

void SoundManager::addSound( std::string path ){
	if(!_sounds.count(path)){
		Mix_Chunk* chunk = Mix_LoadWAV( path.c_str() );
		if(chunk == nullptr){
			printf("Chunk Load Failure : %s\n", Mix_GetError());
		}
		_sounds.emplace(path, chunk);
	}
}

void SoundManager::playSound( std::string path, int volume, int channel, int loops ){
	if(!_sounds.count(path)) addSound(path);
	Mix_Volume(channel, volume);
	if(Mix_PlayChannel(channel, _sounds[path], loops) == -1){
		printf("Sound Play Error: %s\n", Mix_GetError());
	}
}

void SoundManager::playMusic( std::string path, int volume, int loops ){
	/*
	if(!_musics.count(path)) addMusic(path);
	Mix_VolumeMusic(volume);
	if(Mix_PlayMusic(_musics[path], loops) == -1){
		printf("Music Play Error: %s\n", Mix_GetError());
	}*/
	if (!isChannelPlaying(0))
	playSound(path, volume, 0, loops);
}
