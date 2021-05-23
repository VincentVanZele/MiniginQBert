#pragma once
#include <thread>
#include <mutex>
#include <queue>

// Credit to Jakebesworth for the SDL2 audio files and to any feedback that was given in class

namespace dae
{
	class AudioSystem
	{
	public:
		AudioSystem() = default;
		virtual ~AudioSystem() = default;

		AudioSystem(const AudioSystem& other) = delete;
		AudioSystem(AudioSystem&& other) noexcept = delete;
		AudioSystem& operator=(const AudioSystem& other) = delete;
		AudioSystem& operator=(AudioSystem&& other) noexcept = delete;

		virtual void Initialize() = 0;
		virtual void Destroy() = 0;

		virtual void AddAudio(const char* filename, int volume, bool isSound) = 0;
		
		virtual void PlaySound(const char* filename, int volume) = 0;
		virtual void PlayMusic(const char* filename, int volume) = 0;

		virtual void Mute() = 0;
		virtual void Unmute() = 0;

		//virtual void PlayLoadedSound(Audio* audioObject, int volume) = 0;
		//virtual void PlayLoadedMusic(Audio* audioObject, int volume) = 0;
		
		//virtual void PauseAudio() = 0;
		//virtual void UnpauseAudio() = 0;
		
		//virtual void StopAudio() = 0;
		//virtual void FreeAudio(Audio* audioObject) = 0;
		
	};

	class NullAudioSystem final : public AudioSystem
	{
	public:
		~NullAudioSystem() override = default;

		virtual void Initialize() override {};
		virtual void Destroy() override {};

		void AddAudio(const char*, int, bool) override {};

		void PlaySound(const char* , int ) override{};
		void PlayMusic(const char* , int ) override {};

		virtual void Mute() override {};
		virtual void Unmute() override {};

		//void PlayLoadedSound(Audio* , int ) override {};
		//void PlayLoadedMusic(Audio* , int ) override {};

		//void PauseAudio() override {};
		//void UnpauseAudio() override {};

		//void StopAudio() override {};
		//void FreeAudio(Audio* ) override {};
	};

	class DirectAudioSystem final : public AudioSystem
	{
	public:
		DirectAudioSystem();
		~DirectAudioSystem() override;

		virtual void Initialize() override;
		virtual void Destroy() override;

		virtual void AddAudio(const char* filename, int volume, bool isSound) override;
		
		virtual void PlaySound(const char* filename, int volume) override;
		virtual void PlayMusic(const char* filename, int volume) override;

		virtual void Mute() override;
		virtual void Unmute() override;

		//virtual void PlayLoadedSound(Audio* audioObject, int volume) override;
		//virtual void PlayLoadedMusic(Audio* audioObject, int volume) override;

		//virtual void PauseAudio() override;
		//virtual void UnpauseAudio() override;

		//virtual void StopAudio() override;
		//virtual void FreeAudio(Audio* audioObject) override;

	protected:

		struct AudioObject
		{
			AudioObject(int volume, bool isSound, std::string file)
				:_volume(volume)
				,_isSound(isSound)
				,_filename(file)
			{}

			
			int _volume;
			bool _isSound;
			std::string _filename;
		};
		
		void Update();
	
	private:
		bool m_Play{ false };
		
		std::thread m_AudioThread;
		std::mutex m_AudioMutex;

		std::atomic<bool> m_isPlaying;
		std::condition_variable m_isActive{};

		std::queue<AudioObject> m_AudioQueue{};

		std::string m_DataString = "../Data/";
	};
}