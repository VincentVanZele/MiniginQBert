#include "MiniginPCH.h"
#include "ServiceLocator.h"

#include "Structs.h"

#include "InputManager.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "AudioSystem.h"

#include "Renderer.h"
#include "GameTime.h"

std::shared_ptr<dae::SDLWindowInfo> dae::ServiceLocator::m_pWindowInfo{};

std::shared_ptr<dae::InputManager> dae::ServiceLocator::m_pInputManager{};
std::shared_ptr<dae::ResourceManager> dae::ServiceLocator::m_pResourceManager{};
std::shared_ptr<dae::SceneManager> dae::ServiceLocator::m_pSceneManager{};

dae::NullAudioSystem dae::ServiceLocator::m_pNullAudioSystem{};
dae::AudioSystem* dae::ServiceLocator::m_pAudioSystem{ &m_pNullAudioSystem };
				
std::shared_ptr<dae::Renderer> dae::ServiceLocator::m_pRenderer{};
std::shared_ptr<dae::GameTime> dae::ServiceLocator::m_pGameTime{};

void dae::ServiceLocator::Initialize(float windowX, float windowY)
{
	m_pWindowInfo = std::make_shared<SDLWindowInfo>();
	m_pWindowInfo->_x = windowX;
	m_pWindowInfo->_y = windowY;

	SetInputManager(std::make_shared<InputManager>());
	SetResourceManager(std::make_shared<ResourceManager>());
	SetSceneManager(std::make_shared<SceneManager>());

	SetRenderer(std::make_shared<Renderer>());
	SetGameTime(std::make_shared<GameTime>());
}

void dae::ServiceLocator::SetWindowInfo(std::shared_ptr<dae::SDLWindowInfo> window)
{
	m_pWindowInfo = window;
}

void dae::ServiceLocator::SetInputManager(std::shared_ptr<InputManager> input)
{
	m_pInputManager = input;
}

void dae::ServiceLocator::SetResourceManager(std::shared_ptr<ResourceManager> resource)
{
	m_pResourceManager = resource;
}

void dae::ServiceLocator::SetSceneManager(std::shared_ptr<SceneManager> scene)
{
	m_pSceneManager = scene;
}

void dae::ServiceLocator::SetRenderer(std::shared_ptr<Renderer> renderer)
{
	m_pRenderer = renderer;
}

void dae::ServiceLocator::SetGameTime(std::shared_ptr<GameTime> gameTime)
{
	m_pGameTime = gameTime;
}

void dae::ServiceLocator::SetAudioSystem(dae::AudioSystem* audioSystem)
{
	m_pAudioSystem = audioSystem == nullptr ? &m_pNullAudioSystem : audioSystem;
}
