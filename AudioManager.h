#pragma once

#include "Game.h"

class AudioManager
{
public:
	AudioManager();
	~AudioManager();

	void loadMusic(const char* path);
	void loadSoundEffect(const char* path);
	void playMusic();
	void playSoundEffect();
	void pauseMusic();
	void resumeMusic();
	void stopMusic();
	
	bool musicPaused() { return isMusicPaused; }
	bool musicStoped();
	

private:

	bool isMusicPaused;
	bool isMusicStoped;

	Mix_Music* music;
	Mix_Chunk* soundEffect;
};

