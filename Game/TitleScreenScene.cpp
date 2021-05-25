#include "pch.h"
#include "TitleScreenScene.h"

#include "GameObject.h"
#include "ServiceLocator.h"
#include "ResourceManager.h"
#include "FPSCounter.h"

#include "FPSComponent.h"
#include "GameTime.h"
#include "Player.h"
#include "ScoreComponent.h"
#include "ScoreObserver.h"
#include "TextComponent.h"
#include "TextureComponent.h"
#include "TransformComponent.h"
#include "WorldGrid.h"


dae::TitleScreenScene::TitleScreenScene()
	: Scene("Title")
{
	Initialize();
}

void dae::TitleScreenScene::Initialize()
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
	m_pSprite->GetActiveAnimation().SetPos(Float2{100,10});

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
	auto*  fpsCounter = new FPSCounter();
	auto*  fpsComp = new FPSComponent();
	auto*  textComp = new TextComponent(font3);

	textComp->SetColor({ 255,0,0 });
	fpsGo->AddComponent(fpsCounter);
	fpsGo->AddComponent(textComp);
	fpsGo->AddComponent(fpsComp);

	fpsGo->GetTransform()->Translate(Float2{ 10, 455 });

	Add(fpsGo);

	// WORLD
	auto level = std::make_shared<GameObject>();

	m_world = new WorldGrid(8, Float2(200, 300), level);
	level->AddComponent(m_world);

	// Player
	auto player = std::make_shared<GameObject>();

	m_player = new Player(m_world->GetCubeAtIndex(0));
	player->AddComponent(m_player);
	
	m_player->AddObserver(new ScoreObserver());

	Add(level);
	Add(player);

	// Score
	auto scoreGo = std::make_shared<GameObject>();

	textComp = new TextComponent(font3);
	textComp->SetColor(Float3{ 255,119,0 });
	scoreGo->AddComponent(textComp);
	auto scoreComp = new ScoreComponent(m_player->GetSubject()->GetObserver<ScoreObserver>());
	
	scoreGo->AddComponent(scoreComp);

	scoreGo->GetTransform()->Translate(Float2{ 10, 155 });

	Add(scoreGo);
}

void dae::TitleScreenScene::Update()
{
	//m_score->SetText(std::to_string(m_player->GetScore()));
	Scene::Update();
}
