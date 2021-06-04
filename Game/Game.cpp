#include "pch.h"
#include "Game.h"

#include "SceneManager.h"
#include "ResourceManager.h"

#include "Scene.h"
#include "GameObject.h"
#include "TextObject.h"
#include "DieObserver.h"

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

void dae::Game::SwitchScene()
{
	std::shared_ptr<Scene> scene = std::make_shared<TestScene>();

	SceneManager::GetInstance().AddScene(scene);
	SceneManager::GetInstance().SetActiveScene(scene->GetName());
}

void dae::Game::SwitchLevel1()
{
	std::shared_ptr<Scene> scene = std::make_shared<Level1>();

	SceneManager::GetInstance().AddScene(scene);
	SceneManager::GetInstance().DeleteScene("Title");
	SceneManager::GetInstance().SetActiveScene(scene->GetName());
}
void dae::Game::SwitchLevel2()
{
	std::shared_ptr<Scene> scene = std::make_shared<Level2>();

	SceneManager::GetInstance().AddScene(scene);
	SceneManager::GetInstance().SetActiveScene(scene->GetName());
}
void dae::Game::SwitchLevel3()
{
	std::shared_ptr<Scene> scene = std::make_shared<Level3>();

	SceneManager::GetInstance().AddScene(scene);
	SceneManager::GetInstance().SetActiveScene(scene->GetName());
}

void dae::Game::SwitchVersus()
{
	std::shared_ptr<Scene> scene = std::make_shared<Versus>();

	SceneManager::GetInstance().AddScene(scene);
	SceneManager::GetInstance().SetActiveScene(scene->GetName());
}

void dae::Game::SwitchEndScreen()
{
	SceneManager::GetInstance().SetActiveScene("Title");
	/*std::shared_ptr<Scene> scene = std::make_shared<TestScene>();

	SceneManager::GetInstance().AddScene(scene);
	SceneManager::GetInstance().SetActiveScene(scene->GetName());*/
}

