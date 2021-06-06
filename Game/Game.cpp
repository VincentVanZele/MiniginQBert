#include "pch.h"
#include "Game.h"

#include "SceneManager.h"
#include "ResourceManager.h"

#include "Scene.h"
#include "GameObject.h"
#include "TextObject.h"
#include "DieObserver.h"
#include "EndScreen.h"

#include "FPSComponent.h"
#include "FPSCounter.h"
#include "GameScene.h"
#include "TextComponent.h"
#include "PlayerComponent.h"
#include "LivesComponent.h"
#include "Renderer.h"
#include "ScoreComponent.h"
#include "ScoreObserver.h"
#include "WorldGrid.h"
#include "Player.h"
#include "GridTile.h"
#include "Level1.h"
#include "Level2.h"
#include "Level3.h"
#include "TestScene.h"
#include "TitleScreenScene.h"
#include "Versus.h"
#include "WorldComponent.h"

void dae::Game::Run()
{
	dae::Minigin engine{};
	engine.Window();

	LoadScenes();

	engine.Run();
}

void dae::Game::LoadScenes()
{
	std::shared_ptr<Scene> scene = std::make_shared<TitleScreenScene>();

	SceneManager::GetInstance().AddScene(scene);

	SceneManager::GetInstance().SetActiveScene(scene->GetName());
}

void dae::Game::LoadAllScenes()
{
	// Just to test out FPS and Update method
	/*
	std::shared_ptr<Scene> scene = std::make_shared<TitleScreenScene>();
	std::shared_ptr<Scene> scene2 = std::make_shared<TestScene>();
	std::shared_ptr<Scene> scene3 = std::make_shared<Level1>();
	std::shared_ptr<Scene> scene4 = std::make_shared<Level2>();
	std::shared_ptr<Scene> scene5 = std::make_shared<Level3>();
	std::shared_ptr<Scene> scene6 = std::make_shared<Versus>();
	std::shared_ptr<Scene> scene7 = std::make_shared<EndScreen>();

	SceneManager::GetInstance().AddScene(scene);
	SceneManager::GetInstance().AddScene(scene2);
	SceneManager::GetInstance().AddScene(scene3);
	SceneManager::GetInstance().AddScene(scene4);
	SceneManager::GetInstance().AddScene(scene5);
	SceneManager::GetInstance().AddScene(scene6);
	SceneManager::GetInstance().AddScene(scene7);
	
	SceneManager::GetInstance().SetActiveScene(scene->GetName());*/
}

void dae::Game::SwitchTitle()
{
	/*
	std::shared_ptr<Scene> scene = std::make_shared<TestScene>();

	SceneManager::GetInstance().AddScene(scene);
	SceneManager::GetInstance().SetActiveScene(scene->GetName());
	*/

	SceneManager::GetInstance().SetActiveScene("Title");
}

void dae::Game::SwitchLevel1()
{
	if (!SceneManager::GetInstance().GetScene("Level1"))
	{
		std::shared_ptr<Scene> scene = std::make_shared<Level1>();

		SceneManager::GetInstance().AddScene(scene);
		SceneManager::GetInstance().SetActiveScene(scene->GetName());
	}
	else
	{
		SceneManager::GetInstance().SetActiveScene("Level1");
	}
}
void dae::Game::SwitchLevel2()
{
	if (!SceneManager::GetInstance().GetScene("Level2"))
	{
		std::shared_ptr<Scene> scene = std::make_shared<Level2>();

		SceneManager::GetInstance().AddScene(scene);
		SceneManager::GetInstance().SetActiveScene(scene->GetName());
	}
	else
	{
		SceneManager::GetInstance().SetActiveScene("Level2");
	}
}
void dae::Game::SwitchLevel3()
{
	if (!SceneManager::GetInstance().GetScene("Level3"))
	{
		std::shared_ptr<Scene> scene = std::make_shared<Level3>();

		SceneManager::GetInstance().AddScene(scene);
		SceneManager::GetInstance().SetActiveScene(scene->GetName());
	}
	else
	{
		SceneManager::GetInstance().SetActiveScene("Level3");
	}
}

void dae::Game::SwitchVersus()
{
	if (!SceneManager::GetInstance().GetScene("Versus"))
	{
		std::shared_ptr<Scene> scene = std::make_shared<Versus>();

		SceneManager::GetInstance().AddScene(scene);
		SceneManager::GetInstance().SetActiveScene(scene->GetName());
	}
	else
	{
		SceneManager::GetInstance().SetActiveScene("Versus");
	}
}

void dae::Game::SwitchEndScreen()
{
	SceneManager::GetInstance().DeleteAllScenes();
	
	if (!SceneManager::GetInstance().GetScene("EndScreen"))
	{
		std::shared_ptr<Scene> scene = std::make_shared<EndScreen>();

		SceneManager::GetInstance().AddScene(scene);
		SceneManager::GetInstance().SetActiveScene(scene->GetName());
	}
	else
	{
		SceneManager::GetInstance().SetActiveScene("EndScreen");
	}
}

void dae::Game::Reset()
{	
	std::shared_ptr<Scene> scene = std::make_shared<TitleScreenScene>();

	SceneManager::GetInstance().AddScene(scene);

	SceneManager::GetInstance().SetActiveScene(scene->GetName());
}
