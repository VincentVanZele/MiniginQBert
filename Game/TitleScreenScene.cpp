#include "pch.h"
#include "TitleScreenScene.h"

#include "GameObject.h"
#include "ServiceLocator.h"
#include "ResourceManager.h"
#include "FPSCounter.h"

#include "FPSComponent.h"
#include "GameTime.h"
#include "Player.h"
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
	auto go = std::make_shared<GameObject>();
	auto tex = ServiceLocator::GetResourceManager()->GetInstance().LoadTexture("background.jpg");
	auto texComp = new TextureComponent();
	
	texComp->SetTexture(tex);
	go->AddComponent(texComp);
	Add(go);

	yep = std::make_shared<GameObject>();
	tex = ServiceLocator::GetResourceManager()->GetInstance().LoadTexture("logo.png");
	texComp = new TextureComponent();

	texComp->SetTexture(tex);
	yep->AddComponent(texComp);	
	yep->GetTransform()->Translate(Float2{ 216, 180 });
	Add(yep);

	// FPS
	const auto font3 = ResourceManager::GetInstance().LoadFont("Lingua.otf", 25);

	auto fpsGo = std::make_shared<GameObject>();
	auto*  fpsCounter = new FPSCounter();
	auto*  fpsComp = new FPSComponent();
	auto*  textComp2 = new TextComponent(font3);

	textComp2->SetColor({ 255,0,0 });
	fpsGo->AddComponent(fpsCounter);
	fpsGo->AddComponent(textComp2);
	fpsGo->AddComponent(fpsComp);

	fpsGo->GetTransform()->Translate(Float2{ 10, 1 });

	Add(fpsGo);

	// WORLD
	auto level = std::make_shared<GameObject>();

	m_world = new WorldGrid(8, Float2(200, 300), level);
	level->AddComponent(m_world);

	// Player
	auto player = std::make_shared<GameObject>();

	m_player = new Player();
	player->AddComponent(m_player);
	m_player->SetBaseTile(m_world->GetCubeAtIndex(0));

	Add(level);
	Add(player);
}

void dae::TitleScreenScene::Update()
{
	yep->GetTransform()->Translate(Float2{ 1,0 });

	
	Scene::Update();
}
