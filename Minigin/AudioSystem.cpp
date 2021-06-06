#include "MiniginPCH.h"
#include "AudioSystem.h"
#include "SDL2Audio.h"

// Credit to Jakebesworth for the SDL2 audio files and to any feedback that was given in class

dae::DirectAudioSystem::DirectAudioSystem()
{
	m_isPlaying.store(true);
	auto *audioSystem = this;
	m_AudioThread = std::thread([audioSystem]() {audioSystem->Update(); });
}

dae::DirectAudioSystem::~DirectAudioSystem()
{
	m_isPlaying.store(false);
	m_isActive.notify_one();
	m_AudioThread.join();
}

void dae::DirectAudioSystem::Initialize()
{
	initAudio();
}

void dae::DirectAudioSystem::Destroy()
{
	endAudio();
}

void dae::DirectAudioSystem::Update()
{
	while (m_isPlaying.load())
	{
		while(!m_AudioQueue.empty())
		{
			const AudioObject audioObj = m_AudioQueue.front();
			m_AudioQueue.pop();

			std::unique_lock<std::mutex> mutexLock{ m_AudioMutex };
			
			if (!m_Play)
			{		
				if (audioObj._isSound)
				{
					PlaySound((m_DataString + audioObj._filename).c_str(), int(SDL_MIX_MAXVOLUME * audioObj._volume));
				}
				else
				{
					PlayMusic((m_DataString + audioObj._filename).c_str(), int(SDL_MIX_MAXVOLUME * audioObj._volume));
				}
			}
		}

		std::unique_lock<std::mutex> mutexLock{ m_AudioMutex };
		m_isActive.wait(mutexLock);
	}
}

void dae::DirectAudioSystem::AddAudio(const char* filename, int volume, bool isSound)
{
	const AudioObject audioObj{ volume, isSound, filename };
	std::lock_guard<std::mutex> mutexLock{ m_AudioMutex };
	m_AudioQueue.push(audioObj);
	m_isActive.notify_one();
}

void dae::DirectAudioSystem::PlayMusic(const char* filename, int volume)
{
	playMusic(filename, volume);
}

void dae::DirectAudioSystem::PlaySound(const char* filename, int volume)
{
	playSound(filename, volume);
}

void dae::DirectAudioSystem::Mute()
{
	m_Play = false;
}

void dae::DirectAudioSystem::Unmute()
{
	m_Play = true;
}
