#include "MiniginPCH.h"
/*#include "Audio.h"

#include <iostream>

#include "SDL_mixer.h"
#include <string>

// Direct Audio -----------------------------------------------------
void dae::DirectAudio::Init()
{
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
}

void dae::DirectAudio::Cleanup()
{
	for (size_t i{}; i < m_vpMusic.size(); ++i)
	{
		Mix_FreeMusic(m_vpMusic[i]);
	}
	for (size_t i{}; i < m_vpSounds.size(); ++i)
	{
		Mix_FreeChunk(m_vpSounds[i]);
	}
}

int dae::DirectAudio::AddSound(const std::string& file)
{
	Mix_Chunk* sound = Mix_LoadWAV(file.c_str());

	if (!sound)
	{
		std::string exception{ Mix_GetError() };
		throw std::exception(exception.c_str());
	}

	m_vpSounds.push_back(sound);
	return (int)m_vpSounds.size() - 1;
}

int dae::DirectAudio::AddMusic(const std::string& file)
{
	Mix_Music* sound = Mix_LoadMUS(file.c_str());
	m_vpMusic.push_back(sound);
	return (int)m_vpMusic.size() - 1;
}

void dae::DirectAudio::PlaySound(unsigned int idx)
{
	Mix_PlayChannel(-1, m_vpSounds[idx], 0);
}

void dae::DirectAudio::PlayMusic(unsigned int idx)
{
	Mix_PlayMusic(m_vpMusic[idx], 0);
}

void dae::DirectAudio::StopAllSounds()
{
	Mix_HaltChannel(-1);
}

void dae::DirectAudio::StopAllMusic()
{
	Mix_HaltMusic();
}

// Log Audio -----------------------------------------------------
void dae::LogAudio::Init()
{
	std::cout << "Init()\n";
}

void dae::LogAudio::Cleanup()
{
	std::cout << "Cleanup()\n";
}

int dae::LogAudio::AddSound(const std::string& file)
{
	std::cout << "AddSound() " << file << "\n";
	return 0;
}

int dae::LogAudio::AddMusic(const std::string& file)
{
	std::cout << "AddMusic() " << file << "\n";
	return 0;
}

void dae::LogAudio::PlaySound(unsigned int idx)
{
	std::cout << "PlaySound() " << idx << "\n";
}

void dae::LogAudio::PlayMusic(unsigned int idx)
{
	std::cout << "PlayMusic() " << idx << "\n";
}

void dae::LogAudio::StopAllSounds()
{
	std::cout << "StopAllSounds()\n";
}

void dae::LogAudio::StopAllMusic()
{
	std::cout << "StopAllMusic()\n";
}
*/