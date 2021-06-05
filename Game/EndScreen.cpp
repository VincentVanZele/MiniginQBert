#include "pch.h"
#include "EndScreen.h"

#include "ButtonComponent.h"
#include "GameObject.h"
#include "ServiceLocator.h"
#include "ResourceManager.h"
#include "FPSCounter.h"

#include "InputManager.h"
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
#include "Listener.h"
#include "Event.h"


dae::EndScreen::EndScreen()
	: Scene("EndScreen")
	, m_button{ ButtonBack }
	, m_spSelection{ std::make_shared<GameObject>() }, m_spSelection2{ std::make_shared<GameObject>() }
	, m_lv1Pos{ Float2{ 180.0f, 245.0f } }
{
	Initialize();
}

void dae::EndScreen::Initialize()
{
	// Background
	auto gob = std::make_shared<GameObject>();
	auto texb = ServiceLocator::GetResourceManager()->GetInstance().LoadTexture("background.jpg");
	auto texComp = new TextureComponent();

	texComp->SetTexture(texb);
	gob->AddComponent(texComp);
	Add(gob);

	// Title
	gob = std::make_shared<GameObject>();
	texb = ServiceLocator::GetResourceManager()->GetInstance().LoadTexture("Title.png");
	texComp = new TextureComponent();

	texComp->SetTexture(texb);
	gob->AddComponent(texComp);
	Add(gob);
	gob->GetTransform()->Translate(Float2{ 200, 80 });

	
	// Button 1
	auto resourceManager = ServiceLocator::GetResourceManager();
	Float2 buttonDimension{ 196.0f, 42.0f };

	auto go = std::make_shared<GameObject>();
	auto tex = resourceManager->GetInstance().LoadTexture("ButtonQuit.png");
	auto buttonComp = new ButtonComponent(tex, buttonDimension._x, buttonDimension._y);
	go->AddComponent(buttonComp);
	Add(go);

	go->GetTransform()->Translate(Float2{ 225.0f, 237.0f });
	auto list = std::make_shared<Listener>();
	list->SetNotifyFunction([this]() {this->ButtonClicked(Button::ButtonBack); });
	buttonComp->m_spClick->AddListener(list);

	
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

	// Selection
	auto tex3 = resourceManager->GetInstance().LoadTexture("Right.png");
	sequence = std::make_shared<Animation>(tex3, "right", 2);
	m_selectionComp = new SpriteComponent();

	m_spSelection->GetTransform()->Translate(m_lv1Pos);

	sequence->SetPos(m_spSelection->GetTransform()->GetPosition());
	sequence->SetFrameDeltatime(0.2f);
	m_selectionComp->AddAnimation(sequence);
	m_selectionComp->SetActiveAnimation("right");
	m_spSelection->AddComponent(m_selectionComp);

	Add(m_spSelection);

	tex3 = resourceManager->GetInstance().LoadTexture("Left.png");
	sequence = std::make_shared<Animation>(tex3, "left", 2);
	m_selectionComp2 = new SpriteComponent();

	m_spSelection2->GetTransform()->Translate(Float2{ m_lv1Pos._x + 290, m_lv1Pos._y });

	sequence->SetPos(m_spSelection2->GetTransform()->GetPosition());
	sequence->SetFrameDeltatime(0.2f);
	m_selectionComp2->AddAnimation(sequence);
	m_selectionComp2->SetActiveAnimation("left");
	m_spSelection2->AddComponent(m_selectionComp2);

	Add(m_spSelection2);
}

void dae::EndScreen::Update()
{
	// Selection position
	m_selectionComp->GetActiveAnimation().SetPos(m_spSelection->GetTransform()->GetPosition());
	m_selectionComp2->GetActiveAnimation().SetPos(m_spSelection2->GetTransform()->GetPosition());

	if (InputManager::GetInstance().KeyUp(ControllerButton::BVK, 0))
	{
		switch (m_button)
		{
		case Button::ButtonBack:
			ButtonClicked(Button::ButtonBack);
			return; // do to the reset function 
		default:
			break;
		}
	}

	Scene::Update();
}

void dae::EndScreen::ButtonClicked(Button button)
{
	switch (button)
	{
	case Button::ButtonBack:
		dae::Game::Reset();
		break;
	}
}