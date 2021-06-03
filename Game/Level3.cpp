#include "pch.h"
#include "Level3.h"

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
#include "GridTile.h"

dae::Level3::Level3()
	:Scene("Level3")
{
	Initialize();
}

void dae::Level3::Initialize()
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

	// Player Text
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

	m_world = new WorldGrid(GridType::Reset,10, Float2(200, 300), level);
	level->AddComponent(m_world);

	m_numberTiles = m_world->GetNumberOfChangeableTiles(); // 2 disks

	// Player
	auto player = std::make_shared<GameObject>();

	m_player = new Player(m_world->GetCubeAtIndex(4));
	player->AddComponent(m_player);

	m_player->AddObserver(new ScoreObserver());
	m_player->AddObserver(new DieObserver());
	m_player->AddObserver(new WorldObserver());

	Add(level);
	Add(player);

	// Score Player 1
	auto scoreGo = std::make_shared<GameObject>();

	textComp = new TextComponent(font3);
	textComp->SetColor(Float3{ 255,119,0 });
	scoreGo->AddComponent(textComp);
	auto scoreComp = new ScoreComponent(m_player->GetSubject()->GetObserver<ScoreObserver>());

	scoreGo->AddComponent(scoreComp);
	scoreGo->GetTransform()->Translate(Float2{ 25, 75 });
	Add(scoreGo);

	// Lives
	auto livesGo = std::make_shared<GameObject>();

	textComp = new TextComponent(font3);
	textComp->SetColor(Float3{ 255,119,0 });
	livesGo->AddComponent(textComp);

	auto livesComp = new LivesComponent(m_player->GetSubject()->GetObserver<DieObserver>());

	livesGo->AddComponent(livesComp);
	livesGo->GetTransform()->Translate(Float2{ 25, 50 });
	Add(livesGo);

	// Score Player 2
	scoreGo = std::make_shared<GameObject>();

	textComp = new TextComponent(font3);
	textComp->SetColor(Float3{ 220,70,255 });
	scoreGo->AddComponent(textComp);
	scoreComp = new ScoreComponent(new ScoreObserver());

	scoreGo->AddComponent(scoreComp);

	scoreGo->GetTransform()->Translate(Float2{ 475, 75 });

	Add(scoreGo);

	// Egg purple
	auto eggPurple = std::make_shared<GameObject>();

	m_eggP = new Eggs(m_world->GetCubeAtIndex(11), EggType::Purple, Float2{ m_world->GetCubeAtIndex(11)->GetCenter()._x, 0 }, true);
	eggPurple->AddComponent(m_eggP);
	Add(eggPurple);

	// Egg red
	auto eggRed = std::make_shared<GameObject>();

	m_eggR = new Eggs(m_world->GetCubeAtIndex(13), EggType::Red, Float2{ m_world->GetCubeAtIndex(13)->GetCenter()._x, 0 }, false);
	eggRed->AddComponent(m_eggR);
	Add(eggRed);
}

void dae::Level3::Update()
{
	int yes = m_player->GetSubject()->GetObserver<WorldObserver>()->GetFlippedTiles();

	if (yes == m_numberTiles)
	{
		// win condition met
	}

	Scene::Update();
}
