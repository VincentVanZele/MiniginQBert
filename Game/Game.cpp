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
#include "TextComponent.h"
#include "PlayerComponent.h"
#include "LivesComponent.h"
#include "Renderer.h"
#include "ScoreComponent.h"
#include "ScoreObserver.h"
#include "WorldGrid.h"
#include "GridTile.h"
#include "WorldComponent.h"

dae::Game::Game()
	: Minigin()
{
}

void dae::Game::Initialize()
{
	Test();
	/*if(_isCoop)
	{
		Coop();
	}
	else
	{
		SinglePlayer();
	}*/
}

void dae::Game::Test()
{
	Scene* scene = SceneManager::GetInstance().CreateScene("Game");

	// Background
	auto go = std::make_shared<GameObject>();
	go->SetTexture("background.jpg");
	scene->Add(go);

	go = std::make_shared<GameObject>();
	go->SetTexture("logo.png");
	go->SetPosition(216, 180);
	scene->Add(go);
	
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

	scene->Add(fpsGo);

	// WORLD
	auto level = std::make_shared<GameObject>();

	m_world = new WorldGrid(8, Float2(200,300));	
	level->AddComponent(m_world);
	
	scene->Add(level);
	
	SceneManager::GetInstance().SetActiveScene(scene);
}

void dae::Game::SinglePlayer()
{
	Scene* scene = SceneManager::GetInstance().CreateScene("Game");

	// Background
	auto go = std::make_shared<GameObject>();
	go->SetTexture("background.jpg");
	scene->Add(go);

	go = std::make_shared<GameObject>();
	go->SetTexture("logo.png");
	go->SetPosition(216, 180);
	scene->Add(go);

	// Text
	// different fonts for different sizes
	const auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	auto text = std::make_shared<GameObject>();
	auto* textComp = new TextComponent(font);

	textComp->SetText("Programming 4 Assignment");
	text->AddComponent(textComp);
	text->SetPosition(90, 40);
	scene->Add(text);

	// controlls
	const auto font2 = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	auto controllsGo = std::make_shared<GameObject>();
	auto* controlText = new TextComponent(font2);
	
	controlText->SetText("A = player dies  _  X = kill enemy  _  Y = tile changed color");
	controlText->SetTextSize(20);
	controllsGo->AddComponent(controlText);
	controllsGo->SetPosition(80, 100);
	scene->Add(controllsGo);

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

	scene->Add(fpsGo);

	// Player
	auto player = std::make_shared<GameObject>();

	auto* const dieObs = new DieObserver();
	auto* const scoreObs = new ScoreObserver();

	auto* pPlayerComponent = new PlayerComponent(PlayerIndex::PlayerOne);
	pPlayerComponent->AddObserver(dieObs);
	player->AddComponent(pPlayerComponent);

	auto* worldComp = new WorldComponent();
	worldComp->AddObserver(scoreObs);
	player->AddComponent(worldComp);

	scene->Add(player);

	// Lives
	auto livesGo = std::make_shared<GameObject>();

	auto* const textComp3 = new TextComponent(font3);
	auto* const liveComp = new LivesComponent(player->GetComponent<PlayerComponent>());

	livesGo->AddComponent(textComp3);
	livesGo->AddComponent(liveComp);

	livesGo->SetPosition(525, 10);

	scene->Add(livesGo);

	// Score
	auto scoreGo = std::make_shared<GameObject>();

	auto* const textComp4 = new TextComponent(font3);
	auto* const scoreComp = new ScoreComponent(scoreObs);
	textComp4->SetColor({ 0,255,0 });

	scoreGo->AddComponent(textComp4);
	scoreGo->AddComponent(scoreComp);

	scoreGo->SetPosition(250, 10);

	scene->Add(scoreGo);

	SceneManager::GetInstance().SetActiveScene(scene);
}

void dae::Game::Coop()
{
	Scene* scene = SceneManager::GetInstance().CreateScene("Game");

	// Background
	auto go = std::make_shared<GameObject>();
	go->SetTexture("background.jpg");
	scene->Add(go);

	go = std::make_shared<GameObject>();
	go->SetTexture("logo.png");
	go->SetPosition(216, 180);
	scene->Add(go);

	// Text
	// different fonts for different sizes
	const auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	auto text = std::make_shared<GameObject>();
	auto* textComp = new TextComponent(font);

	textComp->SetText("Programming 4 Assignment");
	text->AddComponent(textComp);
	text->SetPosition(90, 40);
	scene->Add(text);

	// controlls
	const auto font2 = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	auto controllsGo = std::make_shared<GameObject>();
	auto* controlText = new TextComponent(font2);

	controlText->SetText("A = player dies  _  X = kill enemy  _  Y = tile changed color");
	controlText->SetTextSize(20);
	controllsGo->AddComponent(controlText);
	controllsGo->SetPosition(80, 100);
	scene->Add(controllsGo);

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

	scene->Add(fpsGo);

	// Player 1 begin {
	auto player1 = std::make_shared<GameObject>();

	auto* const dieObs1 = new DieObserver();
	auto* const scoreObs1 = new ScoreObserver();

	auto* playerComp1 = new PlayerComponent(PlayerIndex::PlayerOne);
	playerComp1->AddObserver(dieObs1);
	player1->AddComponent(playerComp1);

	auto* worldComp1 = new WorldComponent();
	worldComp1->AddObserver(scoreObs1);
	player1->AddComponent(worldComp1);

	scene->Add(player1);

	// Lives
	auto livesGo1 = std::make_shared<GameObject>();

	auto* const P1textComp1 = new TextComponent(font3);
	auto* const liveComp1 = new LivesComponent(player1->GetComponent<PlayerComponent>());

	livesGo1->AddComponent(P1textComp1);
	livesGo1->AddComponent(liveComp1);

	livesGo1->SetPosition(525, 10);

	scene->Add(livesGo1);

	// Score
	auto scoreGo = std::make_shared<GameObject>();

	auto* const P1textComp2 = new TextComponent(font3);
	auto* const scoreComp1 = new ScoreComponent(scoreObs1);
	P1textComp2->SetColor({ 0,255,0 });

	scoreGo->AddComponent(P1textComp2);
	scoreGo->AddComponent(scoreComp1);

	scoreGo->SetPosition(250, 10);

	scene->Add(scoreGo);
	// Player 1 end }
	// might add the score and lives in a player class
	// but it will create more dependencies and make the class more complex
	// -> is it an issue though ?

	// Player 2 begin {
	auto player2 = std::make_shared<GameObject>();

	auto* const dieObs2 = new DieObserver();
	auto* const scoreObs2 = new ScoreObserver();

	auto* playerComp2 = new PlayerComponent(PlayerIndex::PlayerTwo);
	playerComp2->AddObserver(dieObs2);
	player2->AddComponent(playerComp2);

	auto* worldComp2 = new WorldComponent();
	worldComp2->AddObserver(scoreObs2);
	player2->AddComponent(worldComp2);

	scene->Add(player2);

	// Lives
	auto livesGo2 = std::make_shared<GameObject>();

	auto* const P2textComp1 = new TextComponent(font3);
	auto* const liveComp2 = new LivesComponent(player2->GetComponent<PlayerComponent>());

	livesGo2->AddComponent(P2textComp1);
	livesGo2->AddComponent(liveComp2);

	livesGo2->SetPosition(525, 400);

	scene->Add(livesGo2);

	// Score
	auto scoreGo2 = std::make_shared<GameObject>();

	auto* const P2textComp2 = new TextComponent(font3);
	auto* const scoreComp2 = new ScoreComponent(scoreObs2);
	P2textComp2->SetColor({ 0,255,0 });

	scoreGo2->AddComponent(P2textComp2);
	scoreGo2->AddComponent(scoreComp2);

	scoreGo2->SetPosition(250, 400);

	scene->Add(scoreGo2);
	// Player 2 end }
	// might add the score and lives in a player class
	// but it will create more dependencies and make the class more complex
	// -> is it an issue though ? 

	SceneManager::GetInstance().SetActiveScene(scene);
}
