#include "pch.h"
#include "TitleScreenScene.h"


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


dae::TitleScreenScene::TitleScreenScene()
	: Scene("Title")
	, m_selectedButton{ButtonSolo}
	, m_spSelection{ std::make_shared<GameObject>() }
	, m_soloPos{ Float2{ 180.0f, 245.0f } }, m_coopPos{ Float2{ 180.0f, 300.0f } }, m_exitPos{ Float2{ 180.0f, 360.0f } }
{
	Initialize();
}

void dae::TitleScreenScene::Initialize()
{
	// Background
	auto gob = std::make_shared<GameObject>();
	auto texb = ServiceLocator::GetResourceManager()->GetInstance().LoadTexture("background.jpg");
	auto texComp = new TextureComponent();

	texComp->SetTexture(texb);
	gob->AddComponent(texComp);
	Add(gob);

	// Button
	auto resourceManager = ServiceLocator::GetResourceManager();
	Float2 buttonDimension{ 196.0f, 42.0f };

	auto go = std::make_shared<GameObject>();
	auto tex = resourceManager->GetInstance().LoadTexture("ButtonSolo.png");
	auto buttonComp = new ButtonComponent(tex, buttonDimension._x, buttonDimension._y);
	go->AddComponent(buttonComp);
	Add(go);

	go->GetTransform()->Translate(Float2{ 210.0f, 237.0f });
	auto list = std::make_shared<Listener>();
	list->SetNotifyFunction([this]() {this->ButtonClicked(Button::ButtonSolo); });
	buttonComp->m_spClick->AddListener(list);


	go = std::make_shared<GameObject>();
	tex = resourceManager->GetInstance().LoadTexture("ButtonCoop.png");
	buttonComp = new ButtonComponent(tex, buttonDimension._x, buttonDimension._y);
	go->AddComponent(buttonComp);
	Add(go);

	go->GetTransform()->Translate(Float2{ 210.0f, 295.0f });
	list = std::make_shared<Listener>();
	list->SetNotifyFunction([this]() {this->ButtonClicked(Button::ButtonMultiplayer); });
	buttonComp->GetEvent()->AddListener(list);

	go = std::make_shared<GameObject>();
	tex = resourceManager->GetInstance().LoadTexture("ButtonQuit.png");
	buttonComp = new ButtonComponent(tex, buttonDimension._x, buttonDimension._y);
	go->AddComponent(buttonComp);
	Add(go);

	go->GetTransform()->Translate(Float2{ 210.0f, 353.0f });
	list = std::make_shared<Listener>();
	list->SetNotifyFunction([this]() {this->ButtonClicked(Button::ButtonExit); });
	buttonComp->GetEvent()->AddListener(list);

	auto tex3 = resourceManager->GetInstance().LoadTexture("Fire1.png");
	auto sequence = std::make_shared<Animation>(tex3, "fire2", 4);
	m_selectionComp = new SpriteComponent();

	m_spSelection->GetTransform()->Translate(m_soloPos);

	sequence->SetPos(m_spSelection->GetTransform()->GetPosition());
	sequence->SetFrameDeltatime(0.2f);
	m_selectionComp->AddAnimation(sequence);
	m_selectionComp->SetActiveAnimation("fire2");
	m_spSelection->AddComponent(m_selectionComp);
	Add(m_spSelection);
}

void dae::TitleScreenScene::Update()
{
	// Selection position
	m_selectionComp->GetActiveAnimation().SetPos(m_spSelection->GetTransform()->GetPosition());

	
	if (InputManager::GetInstance().KeyUp(ControllerButton::YVK,0))
	{
		switch (m_selectedButton)
		{
		case Button::ButtonSolo:
			m_selectedButton = Button::ButtonExit;
			m_spSelection->GetTransform()->SetPosition(m_exitPos);
			break;
		case Button::ButtonMultiplayer:
			m_selectedButton = Button::ButtonSolo;
			m_spSelection->GetTransform()->SetPosition(m_soloPos);
			break;
		case Button::ButtonExit:
			m_selectedButton = Button::ButtonMultiplayer;
			m_spSelection->GetTransform()->SetPosition(m_coopPos);
			break;
		default:
			break;
		}
	}
	if (InputManager::GetInstance().KeyUp(ControllerButton::AVK, 0))
	{
		switch (m_selectedButton)
		{
		case Button::ButtonSolo:
			m_selectedButton = Button::ButtonMultiplayer;
			m_spSelection->GetTransform()->SetPosition(m_coopPos);
			break;
		case Button::ButtonMultiplayer:
			m_selectedButton = Button::ButtonExit;
			m_spSelection->GetTransform()->SetPosition(m_exitPos);
			break;
		case Button::ButtonExit:
			m_selectedButton = Button::ButtonSolo;
			m_spSelection->GetTransform()->SetPosition(m_soloPos);
			break;
		default:
			break;
		}
	}
	if (InputManager::GetInstance().KeyUp(ControllerButton::BVK, 0))
	{

		switch (m_selectedButton)
		{
		case Button::ButtonSolo:
			ButtonClicked(Button::ButtonSolo);
			break;
		case Button::ButtonMultiplayer:
			ButtonClicked(Button::ButtonMultiplayer);
			break;
		case Button::ButtonExit:
			ButtonClicked(Button::ButtonExit);
			break;
		default:
			break;
		}
	}
	
	Scene::Update();
}

void dae::TitleScreenScene::ButtonClicked(Button button)
{
	//auto& sceneManager = ServiceLocator::GetSceneManager()->GetInstance();

	switch (button)
	{
	case Button::ButtonSolo:
		dae::Game::SwitchVersus();
		break;
	case Button::ButtonMultiplayer:
		dae::Game::SwitchLevel3();
		break;
	case Button::ButtonExit:
		// no game
		break;
	}
}