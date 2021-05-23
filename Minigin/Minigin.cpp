#include "MiniginPCH.h"
#include "Minigin.h"
#include <chrono>
#include <thread>
#include <SDL.h>

#include "SDL2Audio.h"
#include "AudioSystem.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ServiceLocator.h"
#include "GameTime.h"
#include "ResourceManager.h"

#include "TextObject.h"
#include "GameObject.h"
#include "Scene.h"
#include "FPSComponent.h"

void dae::Minigin::Window() 
{
	const auto width{ 640 }, height{ 480 };
	
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,
		width,	height,
		SDL_WINDOW_OPENGL
	);
	if (window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	ServiceLocator::Initialize(static_cast<float>(width), (static_cast<float>(height)));

	ServiceLocator::GetRenderer()->GetInstance().Initialize(window);

	ServiceLocator::GetResourceManager()->GetInstance().Initialize("../Data/");
	
	_putenv("SDL_AUDIODRIVER=DirectSound");
	SDL_Init(SDL_INIT_AUDIO);
	initAudio();
}

void dae::Minigin::Cleanup()
{
	endAudio();
	Renderer::GetInstance().Destroy();
	SceneManager::GetInstance().Destroy();
	SDL_DestroyWindow(window);
	window = nullptr;
	SDL_Quit();
}

void dae::Minigin::Run()
{
	srand(static_cast<unsigned int>(time(nullptr)));

	const auto audioSystem = new DirectAudioSystem();
	ServiceLocator::SetAudioSystem(audioSystem);
	
	{
		auto t = std::chrono::high_resolution_clock::now();
		
		auto& renderer = ServiceLocator::GetRenderer()->GetInstance();
		auto& sceneManager = ServiceLocator::GetSceneManager()->GetInstance();
		auto& input = ServiceLocator::GetInputManager()->GetInstance();
		auto& gameTime = ServiceLocator::GetGameTime()->GetInstance();
		
		auto lastTime = std::chrono::high_resolution_clock::now();
		float lag = 0.0f;
		const float timeStep = 0.02f;
		bool doContinue = true;
		
		while (doContinue)
		{
			const auto currentTime = std::chrono::high_resolution_clock::now();
			const float deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();
			
			lastTime = currentTime;
			lag += deltaTime;
			doContinue = input.ProcessInput();
			
			while (lag >= timeStep)
			{
				lag -= timeStep;
			}
			
			sceneManager.Update();
			renderer.Render();
			gameTime.Update(deltaTime);
		}
	}
	
	Cleanup();
}
