/****************************************************************************
GFC - Games Fundamental Classes
Copyright (C) 2009-2014 Jarek Francik, Kingston University London

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

   1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgment in the product documentation would be
   appreciated but is not required.

   2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.

   3. This notice may not be removed or altered from any source distribution.

   Jarek Francik
   jarek@kingston.ac.uk
****************************************************************************/
#pragma once

#include "FileMgr.h"

////////////////////////////////////////////////////////////////////////////////
// CSound objects represent sound effects, typically loaded from external files.
// Use CSoundPlayer to play them.

class EXT_DECL CSound
{
	Mix_Chunk *m_pChunk;
	static CFileMgr<Mix_Chunk> c_filemgr;	// File Loader (path resolving and cached loading)

public:

	CSound();
	CSound(std::string filename);			// load sound from file
	CSound(Mix_Chunk *pChunk);				// attach sound directly from SDL_mixer Mix_Chunk structure
	~CSound(void);

	void Load(std::string filename);		// load sound from file
	void Unload();

	void Attach(Mix_Chunk *pChunk);			// attach sound directly from SDL_mixer Mix_Chunk structure
	void Detach();

	// for internal / SDL_mixer use only
	operator Mix_Chunk*()			{ return m_pChunk; }
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////
// The main purpose of objects of this class is to play sounds represented by audio files or CSound objects.
// Typical use:
//   CSoundPlayer player;
//   player.Play(&snd);
// or:
//   CSoundPlayer player;
//   player.Play("my_file.wav");

class EXT_DECL CSoundPlayer
{
	// audio initialisation params
	static int c_frequency;
	static Uint16 c_format;
	static int c_channels;
	static int c_chunksize;
	static int c_cnt;

	int m_nChannel;			// audio channel used
	CSound *m_pSound;		// sound played (current or last)
	Mix_Chunk *m_pChunk;	// chunk played (current or last)


	CSound m_sound;			// used in immediate mode - Play(filename);

public:
	CSoundPlayer();
	~CSoundPlayer(void);

	// Play the sound.
	// A CSoundPlayer object will always play just one sound at a time. To play several sounds
	// in the same time, use several CSoundPlayer objects.
	// The sound can be played once, repeated a specified number of times or looped continously.
	// The sound may also fade in (played with gradually increasing volume).
	// If this function is called while some other sound is playing, any previous sound will be 
	// terminated before the new sound starts. If the fade-in option is used, any previous sound 
	// will be gradually and simultanously faded out to create a smooth transition between sounds.
	// If you call this function to play the same sound more than once, any subsequent calls
	// made while the sound is still playing will be postponed (default action, see below for details).
	//
	// Parameters:
	// pSnd - the sound you want to play.
	// nRep - how many times to repeat the sound AFTER it's played once. Default value of 0
	//        produces no repeatitions (the sound willbe played once). Use -1 for continuous loop.
	// nFadeIn - time [msec] for the sound to fade in. Use 0 for instant play. If any previous sound
	//        is being played by the player while the function is called, it will fade out simultanously
	//        to create a smooth transition between sounds (subject to options setting).
	// bAllowReplay - default value (false) prevents sounds from re-playing - when the same sound is played again 
	//         while it is still being played. Set to true to allow the same sound being re-played.
	void Play(CSound *pSnd, int nRep = 0, int nFadeIn = 0, bool bAllowReplay = false);
	void Play(std::string filename, int nRep = 0, int nFadeIn = 0, bool bAllowReplay = false);
	void PlayOnce(CSound *pSnd, int nRep = 0, int nFadeIn = 0);
	void PlayOnce(std::string filename, int nRep = 0, int nFadeIn = 0);

	CSound *IsPlaying();			// returns the sound being currently played; NULL if none
	CSound *LastPlaying();			// returns the sound being currently or most recently played; NULL if none

	void Pause();					// pauses the sound
	void Resume();					// resumes after the pause
	bool IsPaused();				// returns true if sound paused
	void Volume(float vol);			// sets volume (from 0 = silent to 1 = maximum)
	void Stop();					// stops sound immediately
	void FadeOut(int ms);			// fades out sound, gradually decreasing volume for the time provided [ms]
	void Expire(int ms);			// continues to play the sound for for the time provided [ms] and then stops
	void SetPosition(Sint16 angle, Uint8 distance);	// sets the position of the sound source for the stereo playback;
													// angle provided in degrees (0 for ahead)
													// distance from 0 (closest) to 255 (furthest)

	// Channel number is automatically allocated each time you play a sound - you can only query for this number
	int GetChannel()				{ return m_nChannel; }

	// static global functions for audio-subsystem initialisation
	// you will rarely use them directly - they are called automatically from constructor/destructor
	// use SetAudioParams to change system parameters - but avoid calling while any sound is playing
	static void InitAudio();
	static void DoneAudio();
	static void SetAudioParams(int frequency = 44100, Uint16 format = AUDIO_S16SYS, int channels = 2, int chunksize = 2048);

};
