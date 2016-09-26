// author : Lewis Ward
// program: Tog Of War Game
// date   : 18/11/2014
// © 2016 Lewis Ward. All rights reserved.
#include "Sound.h"

// some of the setup based upon code found here : http://www.lazyfoo.net/SDL_tutorials/lesson11/index.php
Sound::Sound(const char* soundName)
{
	m_music = NULL;

	// open the audio
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) == 1)
	{
		m_fileOk = false;
	}
	else
	{
		// load background music
		m_music = Mix_LoadMUS(soundName);
		// did the song fail to load
		if (m_music == NULL)
		{
			m_fileOk = false;
		}
	}
	// file is ok and set to loop sound
	m_fileOk = true;
	m_loop = -1;
}
Sound::~Sound()
{
	Mix_FreeMusic(m_music);
}
void Sound::play()
{
	// if the music was paused then carry on from where it left off
	if (Mix_PausedMusic() == 1)
	{
		Mix_ResumeMusic();
	}
	else
	{
		Mix_PlayMusic(m_music, m_loop);
	}
}
void Sound::pause()
{
	Mix_PauseMusic();
}
