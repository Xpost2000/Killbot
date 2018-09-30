#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <SDL2/SDL_mixer.h>
#include <map>

//TODO: Make sound class
//	instead of using SDL_Mixer's types directly.
class SoundManager{
	public:
		SoundManager();
		~SoundManager();

		static SoundManager* instance(){
			if(_instance == nullptr) _instance = new SoundManager();
			return _instance;
		}
		
		void addMusic( std::string path );	
		void addSound( std::string path );

		void pauseChannel( int channel ) { Mix_Pause(channel); }
		void resumeChannel( int channel ) { Mix_Resume(channel); }
		void haltChannel( int channel ) { Mix_HaltChannel(channel); }

		void pauseMusic(){ pauseChannel(0); }
		void resumeMusic(){ resumeChannel(0); }
		void haltMusic(){ haltChannel(0); }

		bool isChannelPlaying(int channel) { return Mix_Playing(channel); }
		bool isMusicPlaying() { return isChannelPlaying(0); // I reserve the first channel for music
	    }
		void playSound( std::string path, int volume=85, int channel=-1, int loops=0 );
		void playMusic( std::string path, int volume=100, int loops=0 );
	private:
		std::map<std::string, Mix_Chunk*> _sounds;
		std::map<std::string, Mix_Music*> _musics;
		static SoundManager* _instance;
};

#endif
