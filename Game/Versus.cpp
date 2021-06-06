#include "pch.h"
#include "Versus.h"

#include "GameObject.h"
#include "ServiceLocator.h"
#include "ResourceManager.h"
#include "FPSCounter.h"

#include "FPSComponent.h"
#include "LivesComponent.h"
#include "DieObserver.h"
#include "Player.h"
#include "ScoreComponent.h"
#include "ScoreObserver.h"
#include "TextComponent.h"
#include "TextureComponent.h"
#include "TransformComponent.h"
#include "WorldGrid.h"
#include "WorldObserver.h"
#include "Eggs.h"
#include "Game.h"
#include "GridTile.h"
#include "GameTime.h"

dae::Versus::Versus()
	:Scene("Versus")
{
	Initialize();
}

void dae::Versus::Initialize()
{
	// Background
	auto go = std::make_shared<GameObject>();
	auto tex = ServiceLocator::GetResourceManager()->GetInstance().LoadTexture("background.jpg");
	auto texComp = new TextureComponent();

	texComp->SetTexture(tex);
	go->AddComponent(texComp);
	Add(go);
	
	// Player Text
	go = std::make_shared<GameObject>();
	auto m_pSprite = new SpriteComponent();
	tex = ServiceLocator::GetResourceManager()->GetInstance().LoadTexture("P1_Text.png");
	auto sequence = std::make_shared<Animation>(tex, "P1T", 2);
	m_pSprite->AddAnimation(sequence);
	m_pSprite->SetActiveAnimation("P1T");
	m_pSprite->GetActiveAnimation().SetPos(Float2{ 100,10 });

	go->AddComponent(m_pSprite);

	Add(go);

	// Player Text 2
	go = std::make_shared<GameObject>();
	m_pSprite = new SpriteComponent();
	tex = ServiceLocator::GetResourceManager()->GetInstance().LoadTexture("P2_Text.png");
	sequence = std::make_shared<Animation>(tex, "P2T", 2);
	m_pSprite->AddAnimation(sequence);
	m_pSprite->SetActiveAnimation("P2T");
	m_pSprite->GetActiveAnimation().SetPos(Float2{ 540,10 });

	go->AddComponent(m_pSprite);

	Add(go);

	// FPS
	const auto font3 = ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);

	auto fpsGo = std::make_shared<GameObject>();
	auto* fpsCounter = new FPSCounter();
	auto* fpsComp = new FPSComponent();
	auto* textComp = new TextComponent(font3);

	textComp->SetColor({ 255,0,0 });
	fpsGo->AddComponent(fpsCounter);
	fpsGo->AddComponent(textComp);
	fpsGo->AddComponent(fpsComp);

	fpsGo->GetTransform()->Translate(Float2{ 10, 455 });

	Add(fpsGo);

	// WORLD
	auto level = std::make_shared<GameObject>();

	m_world = new WorldGrid(GridType::Versus, 10, Float2(150, 325), level);
	level->AddComponent(m_world);

	// Player
	auto player = std::make_shared<GameObject>();

	m_player = new Player(m_world->GetCubeAtIndex(4),Player1);
	player->AddComponent(m_player);

	m_player->AddObserver(new DieObserver());
	m_player->AddObserver(new WorldObserver());

	// Player
	auto player2 = std::make_shared<GameObject>();

	m_player2 = new Player(m_world->GetCubeAtIndex(37), Player2);
	player2->AddComponent(m_player2);

	m_player2->AddObserver(new DieObserver());
	m_player2->AddObserver(new WorldObserver());

	// Lives 1 
	auto livesGo = std::make_shared<GameObject>();

	textComp = new TextComponent(font3);
	textComp->SetColor(Float3{ 255,119,0 });
	livesGo->AddComponent(textComp);

	auto livesComp = new LivesComponent(m_player->GetSubject()->GetObserver<DieObserver>());

	livesGo->AddComponent(livesComp);
	livesGo->GetTransform()->Translate(Float2{ 25, 50 });
	Add(livesGo);

	// Lives 2
	livesGo = std::make_shared<GameObject>();

	textComp = new TextComponent(font3);
	textComp->SetColor(Float3{ 255,119,0 });
	livesGo->AddComponent(textComp);

	livesComp = new LivesComponent(m_player2->GetSubject()->GetObserver<DieObserver>());

	livesGo->AddComponent(livesComp);
	livesGo->GetTransform()->Translate(Float2{ 475, 50 });
	Add(livesGo);

	Add(level);
	Add(player);
	Add(player2);
}

void dae::Versus::Update()
{
	m_elapsedTime += ServiceLocator::GetGameTime()->GetInstance().GetDeltaTime();
	int lives = m_player->GetSubject()->GetObserver<DieObserver>()->GetLives();
	int lives2 = m_player2->GetSubject()->GetObserver<DieObserver>()->GetLives();

	if ((m_elapsedTime > m_endTime) || lives < 0 || lives2 < 0)
	{
		if (m_doOnce)
		{
			// win/lose condition met
			m_player->SetMoveRestriction(true);
			m_player2->SetMoveRestriction(true);
			m_doOnce = false;
			dae::Game::SwitchEndScreen();
		}
		return;
	}
	Scene::Update();
}
