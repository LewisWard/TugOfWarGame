// author : Lewis Ward (http://www.lewis-ward.com)
// program: Tug Of War Game
// date   : 18/11/2014
// � 2016 Lewis Ward. All rights reserved.
#pragma once
#include "Window.h"

class Sound
{
public:
	//----------------------------------------------------------------------------------------------------------------------
	/// \brief Constructor
	/// \parma const char* sound file name
	//----------------------------------------------------------------------------------------------------------------------
	Sound(const char* soundName);

	//----------------------------------------------------------------------------------------------------------------------
	/// \brief Destructor
	//----------------------------------------------------------------------------------------------------------------------
	~Sound();

	//----------------------------------------------------------------------------------------------------------------------
	/// \brief play the sound
	//----------------------------------------------------------------------------------------------------------------------
	void play();

	//----------------------------------------------------------------------------------------------------------------------
	/// \brief pause the sound
	//----------------------------------------------------------------------------------------------------------------------
	void pause();

	//----------------------------------------------------------------------------------------------------------------------
	/// \brief get the state of the file
	/// \return bool loaded file
	//----------------------------------------------------------------------------------------------------------------------
	inline bool state() { return m_fileOk; }

	//----------------------------------------------------------------------------------------------------------------------
	/// \brief set if you want to loop the music
	/// \parma int
	//----------------------------------------------------------------------------------------------------------------------
	inline void loop(int loops) { m_loop = loops; }

private:
	Mix_Music* m_music; ///< pointer to sound file
	int m_loop; ///< number of loops
	bool m_fileOk; ///< file loaded ok
};
