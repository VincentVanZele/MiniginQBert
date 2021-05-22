#include "pch.h"
#include "GameScene.h"

#include "SceneManager.h"
#include "ResourceManager.h"

#include "Scene.h"
#include "GameObject.h"
#include "TextObject.h"
#include "DieObserver.h"

#include "FPSComponent.h"
#include "FPSCounter.h"
#include "TextComponent.h"
#include "PlayerComponent.h"
#include "LivesComponent.h"
#include "Renderer.h"
#include "ScoreComponent.h"
#include "ScoreObserver.h"
#include "WorldGrid.h"
#include "Player.h"
#include "GridTile.h"
#include "WorldComponent.h"

dae::GameScene::GameScene()
	:Scene("GameScene")
{
}

void dae::GameScene::Initialize()
{
	// Background
	auto go = std::make_shared<GameObject>();
	go->SetTexture("background.jpg");
	Add(go);

	go = std::make_shared<GameObject>();
	go->SetTexture("logo.png");
	go->SetPosition(216, 180);
	Add(go);

	// FPS
	const auto font3 = ResourceManager::GetInstance().LoadFont("Lingua.otf", 25);

	auto fpsGo = std::make_shared<GameObject>();
	auto* const fpsCounter = new FPSCounter();
	auto* const fpsComp = new FPSComponent();
	auto* const textComp2 = new TextComponent(font3);

	textComp2->SetColor({ 255,0,0 });
	fpsGo->AddComponent(fpsCounter);
	fpsGo->AddComponent(textComp2);
	fpsGo->AddComponent(fpsComp);

	fpsGo->SetPosition(10, 10);

	Add(fpsGo);

	// WORLD
	auto level = std::make_shared<GameObject>();

	m_world = new WorldGrid(8, Float2(200, 300));
	level->AddComponent(m_world);

	// Player
	auto player = std::make_shared<GameObject>();

	m_player = new Player();
	player->AddComponent(m_player);

	Add(player);
	Add(level);
}