#include "AudioManager.h"

using std::cout;
using std::endl;

AudioManager::AudioManager()
{
	music = NULL;
	soundEffect = NULL;
	isMusicPaused = true;
}

AudioManager::~AudioManager()
{
	Mix_FreeMusic(music);
	music = NULL;

	Mix_FreeChunk(soundEffect);
	soundEffect = NULL;
}

void AudioManager::loadMusic(const char* path)
{
	music = Mix_LoadMUS(path);
	if (music == NULL)
	{
		cout << "Failed to load beat music! SDL_mixer Error: " << Mix_GetError() << endl;
	}
}

void AudioManager::loadSoundEffect(const char* path)
{
	soundEffect = Mix_LoadWAV(path);
	if (soundEffect == NULL)
	{
		cout << "Failed to load sound effect! SDL_mixer Error: " << Mix_GetError() << endl;
	}
}

void AudioManager::playMusic()
{
	if (music == NULL)
	{
		cout << "Music not loaded!" << endl;
	}
	else
	{
		if (Mix_PlayingMusic() == 0)
		{
			Mix_PlayMusic(music, -1);

			isMusicPaused = false;
		}
	}
}

void AudioManager::playSoundEffect()
{
	if (soundEffect == NULL)
	{
		cout << "Sound effect not loaded!" << endl;
	}
	else
	{
		if (Mix_PlayChannel(-1, soundEffect, 0) == -1)
		{
			cout << "Failed to play sound effect! SDL_mixer Error: " << SDL_GetError() << endl;
		}
	}
}

void AudioManager::pauseMusic()
{
	if (Mix_PlayingMusic() != 0)
	{
		Mix_PauseMusic();

		isMusicPaused = true;
	}
}

void AudioManager::resumeMusic()
{
	if (Mix_PlayingMusic() != 0)
	{
		if (Mix_PausedMusic() == 1)
		{
			Mix_ResumeMusic();

			isMusicPaused = false;
		}
	}
}

void AudioManager::stopMusic()
{
	if (Mix_PlayingMusic() != 0)
	{
		Mix_HaltMusic();
	}
}

bool AudioManager::musicStoped()
{
	if (Mix_PlayingMusic() != 0)
	{
		isMusicStoped = false;
	}
	else
	{
		isMusicStoped = true;
	}
	//isMusicStoped == Mix_PlayingMusic();
	return isMusicStoped;
}