#pragma once
#include "Structs.h"

namespace dae
{
	class InputManager;
	class ResourceManager;
	class SceneManager;
	class NullAudioSystem;
	class AudioSystem;

	class Renderer;
	class GameTime;
	
	class ServiceLocator final 
	{
	public:
		static void Initialize(float windowX, float windowY);

		// Window Info
		static std::shared_ptr<dae::SDLWindowInfo> GetWindowInfo() { return m_pWindowInfo; }
		static void SetWindowInfo(std::shared_ptr<dae::SDLWindowInfo> window);

		// Input Manager
		static std::shared_ptr<dae::InputManager> GetInputManager() { return m_pInputManager; }
		static void SetInputManager(std::shared_ptr<dae::InputManager> input);
		
		// Resource Manager
		static std::shared_ptr<dae::ResourceManager> GetResourceManager() { return m_pResourceManager; }
		static void SetResourceManager(std::shared_ptr<dae::ResourceManager> resource);

		// Scene Manager
		static std::shared_ptr<dae::SceneManager> GetSceneManager() { return m_pSceneManager; }
		static void SetSceneManager(std::shared_ptr<dae::SceneManager> scene);

		// Renderer
		static std::shared_ptr<dae::Renderer> GetRenderer() { return m_pRenderer; }
		static void SetRenderer(std::shared_ptr<dae::Renderer> renderer);

		// Game Time
		static std::shared_ptr<dae::GameTime> GetGameTime() { return m_pGameTime; }
		static void SetGameTime(std::shared_ptr<dae::GameTime> gameTime);

		// Audio System
		static dae::AudioSystem& GetAudioSystem() { return *m_pAudioSystem; }
		static void SetAudioSystem(dae::AudioSystem* audioSystem);

	private:
		static std::shared_ptr<dae::SDLWindowInfo> m_pWindowInfo;

		static std::shared_ptr<dae::InputManager> m_pInputManager;
		static std::shared_ptr<dae::ResourceManager> m_pResourceManager;
		static std::shared_ptr<dae::SceneManager> m_pSceneManager;

		static dae::NullAudioSystem m_pNullAudioSystem;
		static dae::AudioSystem* m_pAudioSystem;

		static std::shared_ptr<dae::Renderer> m_pRenderer;
		static std::shared_ptr<dae::GameTime> m_pGameTime;
	};
};