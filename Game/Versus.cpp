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
}

void dae::Versus::Update()
{

	Scene::Update();
}
