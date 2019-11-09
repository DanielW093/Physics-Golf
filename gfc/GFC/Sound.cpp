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
#include "stdafx.h"
#include "..\GFC\include\GFC.h"

int CSoundPlayer::c_frequency = 44100;
Uint16 CSoundPlayer::c_format = AUDIO_S16SYS;
int CSoundPlayer::c_channels = 2;
int CSoundPlayer::c_chunksize = 2048;
int CSoundPlayer::c_cnt = 0;

CFileMgr<Mix_Chunk> CSound::c_filemgr("%;%sounds\\;.\\;sounds\\",
										[](std::string filename) 
										{ 
											return Mix_LoadWAV(filename.c_str()); 
										},
										[](Mix_Chunk* pChunk) 
										{ 
											Mix_FreeChunk(pChunk);
										});

//////////////////////////////////////////////////////////////////////////////////////////////
// CSound

CSound::CSound()
{
	CSoundPlayer::InitAudio();
	m_pChunk = NULL;
}

CSound::CSound(std::string filename)
{
	CSoundPlayer::InitAudio();
	m_pChunk = NULL;
	Load(filename);
}

CSound::CSound(Mix_Chunk *pChunk)
{
	CSoundPlayer::InitAudio();
	m_pChunk = NULL;
	Attach(pChunk);
}

CSound::~CSound(void)
{
	Unload();
	CSoundPlayer::DoneAudio();
}

void CSound::Load(std::string filename)
{
	Unload();
	m_pChunk = c_filemgr.Load(filename);
}

void CSound::Unload()
{
	// nothing special to do - chunks are cached somewhere else
	m_pChunk = NULL;
}

void CSound::Attach(Mix_Chunk *pChunk)
{
	Unload();
	m_pChunk = pChunk;
}

void CSound::Detach()
{
	Unload();
}

//////////////////////////////////////////////////////////////////////////////////////////////
// CSoundPlayer

CSoundPlayer::CSoundPlayer()
{
	InitAudio();
	m_nChannel = -1;
	m_pSound = NULL;
	m_pChunk = NULL;
}

CSoundPlayer::~CSoundPlayer(void)
{
	DoneAudio();
}

void CSoundPlayer::InitAudio()
{
	if (c_cnt++ == 0)
		Mix_OpenAudio(c_frequency, c_format, c_channels, c_chunksize);
}

void CSoundPlayer::DoneAudio()
{
	if (--c_cnt == 0)
		Mix_CloseAudio();
}

void CSoundPlayer::SetAudioParams(int frequency, Uint16 format, int channels, int chunksize)
{
	c_frequency = frequency;
	c_format = format;
	c_channels = channels;
	c_chunksize = chunksize;
	if (c_cnt)
	{
		Mix_CloseAudio();
		Mix_OpenAudio(c_frequency, c_format, c_channels, c_chunksize);
	}
}

void CSoundPlayer::Play(CSound *pSnd, int nRep, int nFadeIn, bool bAllowReplay)
{
	Mix_Chunk *pChunk = pSnd ? *pSnd : NULL;
	if (IsPlaying())
	{
		if (!bAllowReplay && m_pChunk == pChunk) return;
		if (nFadeIn)
			Mix_FadeOutChannel(m_nChannel, nFadeIn);
		else
			Mix_HaltChannel(m_nChannel);
	}

	m_pSound = pSnd;
	m_pChunk = pChunk;
	if (!m_pSound || !m_pChunk)
		return;

	if (nFadeIn)
		m_nChannel = Mix_FadeInChannel(-1, m_pChunk, nRep, nFadeIn);
	else
		m_nChannel = Mix_PlayChannel(-1, m_pChunk, nRep);
}

void CSoundPlayer::Play(std::string filename, int nRep, int nFadeIn, bool bAllowReplay)
{
	m_sound.Load(filename);
	Play(&m_sound, nRep, nFadeIn, bAllowReplay);
}

void CSoundPlayer::PlayOnce(CSound *pSnd, int nRep, int nFadeIn)
{
	Mix_Chunk *pChunk = pSnd ? *pSnd : NULL;
	if (m_pChunk == pChunk) return;
	Play(pSnd, nRep, nFadeIn);
}

void CSoundPlayer::PlayOnce(std::string filename, int nRep, int nFadeIn)
{
	m_sound.Load(filename);
	PlayOnce(&m_sound, nRep, nFadeIn);
}

CSound *CSoundPlayer::IsPlaying()
{ 
	if (m_nChannel < 0 || m_pSound == NULL)
		return false;
	else if (Mix_Playing(m_nChannel) != 0)
		return m_pSound;
	m_nChannel = -1;
	return false;
}

CSound *CSoundPlayer::LastPlaying()		{ return m_pSound; }

void CSoundPlayer::Pause()				{ if (IsPlaying()) Mix_Pause(m_nChannel); }
void CSoundPlayer::Resume()				{ if (IsPlaying()) Mix_Resume(m_nChannel); }
bool CSoundPlayer::IsPaused()			{ return Mix_Paused(m_nChannel) != 0; }
void CSoundPlayer::Volume(float vol)	{ if (IsPlaying()) Mix_Volume(m_nChannel, (int)(vol * 128)); }
void CSoundPlayer::Stop()				{ if (IsPlaying()) Mix_HaltChannel(m_nChannel); m_nChannel = -1; }
void CSoundPlayer::FadeOut(int ms)		{ if (IsPlaying()) Mix_FadeOutChannel(m_nChannel, ms); }
void CSoundPlayer::Expire(int ms)		{ if (IsPlaying()) Mix_ExpireChannel(m_nChannel, ms); }

void CSoundPlayer::SetPosition(Sint16 angle, Uint8 distance)	{ Mix_SetPosition(m_nChannel, angle, distance); }
