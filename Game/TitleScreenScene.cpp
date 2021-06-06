#include "pch.h"
#include "TitleScreenScene.h"


#include "ButtonComponent.h"
#include "GameObject.h"
#include "ServiceLocator.h"
#include "ResourceManager.h"
#include "FPSCounter.h"

#include "AudioSystem.h"
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
	, m_selectedButton{ButtonLevel1}
	, m_spSelection{ std::make_shared<GameObject>() }, m_spSelection2{ std::make_shared<GameObject>() }
	, m_lv1Pos{ Float2{ 180.0f, 245.0f } }, m_lv2Pos{ Float2{ 180.0f, 300.0f } }, m_lv3Pos{ Float2{ 180.0f, 360.0f } }, m_vsPos{ Float2{ 180.0f, 400.0f } }
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

	// Title
	gob = std::make_shared<GameObject>();
	texb = ServiceLocator::GetResourceManager()->GetInstance().LoadTexture("Title.png");
	texComp = new TextureComponent();

	texComp->SetTexture(texb);
	gob->AddComponent(texComp);
	Add(gob);
	gob->GetTransform()->Translate(Float2{ 200, 80 });

	// text
	const auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);

	auto textGo = std::make_shared<GameObject>();
	auto textComp = new TextComponent(font,"Y (or Controller Y) = Up / H (or Controller A) = Down / Space = Select",Float3{255,0,0});
	textGo->AddComponent(textComp);
	Add(textGo);

	textGo->GetTransform()->Translate(Float2{ 10,175 });

	// Controls P2
	// A
	auto goc = std::make_shared<GameObject>();
	auto texc = ServiceLocator::GetResourceManager()->GetInstance().LoadTexture("A.png");
	auto texCompc = new TextureComponent();

	texCompc->SetTexture(texc);
	goc->AddComponent(texCompc);
	
	Add(goc);
	goc->GetTransform()->Translate(Float2{ 500, 100 });

	// Q
	goc = std::make_shared<GameObject>();
	texc = ServiceLocator::GetResourceManager()->GetInstance().LoadTexture("Q.png");
	texCompc = new TextureComponent();

	texCompc->SetTexture(texc);
	goc->AddComponent(texCompc);

	Add(goc);
	goc->GetTransform()->Translate(Float2{ 500, 50 });

	// E
	goc = std::make_shared<GameObject>();
	texc = ServiceLocator::GetResourceManager()->GetInstance().LoadTexture("E.png");
	texCompc = new TextureComponent();

	texCompc->SetTexture(texc);
	goc->AddComponent(texCompc);

	Add(goc);
	goc->GetTransform()->Translate(Float2{ 550, 50 });

	// D
	goc = std::make_shared<GameObject>();
	texc = ServiceLocator::GetResourceManager()->GetInstance().LoadTexture("D.png");
	texCompc = new TextureComponent();

	texCompc->SetTexture(texc);
	goc->AddComponent(texCompc);

	Add(goc);
	goc->GetTransform()->Translate(Float2{ 550, 100 });

	// Controls P1
	// X
	goc = std::make_shared<GameObject>();
	texc = ServiceLocator::GetResourceManager()->GetInstance().LoadTexture("XC.png");
	texCompc = new TextureComponent();

	texCompc->SetTexture(texc);
	goc->AddComponent(texCompc);

	Add(goc);
	goc->GetTransform()->Translate(Float2{ 50, 100 });

	// Y
	goc = std::make_shared<GameObject>();
	texc = ServiceLocator::GetResourceManager()->GetInstance().LoadTexture("YC.png");
	texCompc = new TextureComponent();

	texCompc->SetTexture(texc);
	goc->AddComponent(texCompc);

	Add(goc);
	goc->GetTransform()->Translate(Float2{ 50, 50 });

	// B
	goc = std::make_shared<GameObject>();
	texc = ServiceLocator::GetResourceManager()->GetInstance().LoadTexture("BC.png");
	texCompc = new TextureComponent();

	texCompc->SetTexture(texc);
	goc->AddComponent(texCompc);

	Add(goc);
	goc->GetTransform()->Translate(Float2{ 100, 50 });

	// A
	goc = std::make_shared<GameObject>();
	texc = ServiceLocator::GetResourceManager()->GetInstance().LoadTexture("AC.png");
	texCompc = new TextureComponent();

	texCompc->SetTexture(texc);
	goc->AddComponent(texCompc);

	Add(goc);
	goc->GetTransform()->Translate(Float2{ 100, 95 });

	// Button 1
	auto resourceManager = ServiceLocator::GetResourceManager();
	Float2 buttonDimension{ 196.0f, 42.0f };

	auto go = std::make_shared<GameObject>();
	auto tex = resourceManager->GetInstance().LoadTexture("ButtonLvl1.png");
	auto buttonComp = new ButtonComponent(tex, buttonDimension._x, buttonDimension._y);
	go->AddComponent(buttonComp);
	Add(go);

	go->GetTransform()->Translate(Float2{ 225.0f, 237.0f });
	auto list = std::make_shared<Listener>();
	list->SetNotifyFunction([this]() {this->ButtonClicked(Button::ButtonLevel1); });
	buttonComp->m_spClick->AddListener(list);

	// button 2
	go = std::make_shared<GameObject>();
	tex = resourceManager->GetInstance().LoadTexture("ButtonLvl2.png");
	buttonComp = new ButtonComponent(tex, buttonDimension._x, buttonDimension._y);
	go->AddComponent(buttonComp);
	Add(go);

	go->GetTransform()->Translate(Float2{ 225.0f, 295.0f });
	list = std::make_shared<Listener>();
	list->SetNotifyFunction([this]() {this->ButtonClicked(Button::ButtonLevel2); });
	buttonComp->GetEvent()->AddListener(list);

	// button 3
	go = std::make_shared<GameObject>();
	tex = resourceManager->GetInstance().LoadTexture("ButtonLvl3.png");
	buttonComp = new ButtonComponent(tex, buttonDimension._x, buttonDimension._y);
	go->AddComponent(buttonComp);
	Add(go);

	go->GetTransform()->Translate(Float2{ 225.0f, 353.0f });
	list = std::make_shared<Listener>();
	list->SetNotifyFunction([this]() {this->ButtonClicked(Button::ButtonLevel3); });
	buttonComp->GetEvent()->AddListener(list);

	// button Versus
	go = std::make_shared<GameObject>();
	tex = resourceManager->GetInstance().LoadTexture("ButtonVersus.png");
	buttonComp = new ButtonComponent(tex, buttonDimension._x, buttonDimension._y);
	go->AddComponent(buttonComp);
	Add(go);

	go->GetTransform()->Translate(Float2{ 225.0f, 407.0f });
	list = std::make_shared<Listener>();
	list->SetNotifyFunction([this]() {this->ButtonClicked(Button::ButtonVersus); });
	buttonComp->GetEvent()->AddListener(list);

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

	InputManager::GetInstance().AddInput("space", ' ');
	InputManager::GetInstance().AddInput("Select_Up", 'y');
	InputManager::GetInstance().AddInput("Select_Down", 'h');
}

void dae::TitleScreenScene::Update()
{
	// Selection position
	m_selectionComp->GetActiveAnimation().SetPos(m_spSelection->GetTransform()->GetPosition());
	m_selectionComp2->GetActiveAnimation().SetPos(m_spSelection2->GetTransform()->GetPosition());
	
	if (InputManager::GetInstance().KeyUp(ControllerButton::YVK,0) || InputManager::GetInstance().KeyUp("Select_Up"))
	{
		switch (m_selectedButton)
		{
		case Button::ButtonLevel1:
			m_selectedButton = Button::ButtonVersus;
			m_spSelection->GetTransform()->SetPosition(m_vsPos);
			m_spSelection2->GetTransform()->SetPosition(Float2{ m_vsPos._x + 290, m_vsPos._y });
			break;
		case Button::ButtonLevel2:
			m_selectedButton = Button::ButtonLevel1;
			m_spSelection->GetTransform()->SetPosition(m_lv1Pos);
			m_spSelection2->GetTransform()->SetPosition(Float2{ m_lv1Pos._x + 290, m_lv1Pos._y });
			break;
		case Button::ButtonLevel3:
			m_selectedButton = Button::ButtonLevel2;
			m_spSelection->GetTransform()->SetPosition(m_lv2Pos);
			m_spSelection2->GetTransform()->SetPosition(Float2{ m_lv2Pos._x + 290, m_lv2Pos._y });
			break;
		case Button::ButtonVersus:
			m_selectedButton = Button::ButtonLevel3;
			m_spSelection->GetTransform()->SetPosition(m_lv3Pos);
			m_spSelection2->GetTransform()->SetPosition(Float2{ m_lv3Pos._x + 290, m_lv3Pos._y });
			break;
		default:
			break;
		}

		ServiceLocator::GetAudioSystem().AddAudio("Sound/die.WAV", 1, true);
	}
	if (InputManager::GetInstance().KeyUp(ControllerButton::AVK, 0) || InputManager::GetInstance().KeyUp("Select_Down"))
	{
		switch (m_selectedButton)
		{
		case Button::ButtonLevel1:
			m_selectedButton = Button::ButtonLevel2;
			m_spSelection->GetTransform()->SetPosition(m_lv2Pos);
			m_spSelection2->GetTransform()->SetPosition(Float2{ m_lv2Pos._x + 290, m_lv2Pos._y });
			break;
		case Button::ButtonLevel2:
			m_selectedButton = Button::ButtonLevel3;
			m_spSelection->GetTransform()->SetPosition(m_lv3Pos);
			m_spSelection2->GetTransform()->SetPosition(Float2{ m_lv3Pos._x + 290, m_lv3Pos._y });
			break;
		case Button::ButtonLevel3:
			m_selectedButton = Button::ButtonVersus;
			m_spSelection->GetTransform()->SetPosition(m_vsPos);
			m_spSelection2->GetTransform()->SetPosition(Float2{ m_vsPos._x + 290, m_vsPos._y });
			break;
		case Button::ButtonVersus:
			m_selectedButton = Button::ButtonLevel1;
			m_spSelection->GetTransform()->SetPosition(m_lv1Pos);
			m_spSelection2->GetTransform()->SetPosition(Float2{ m_lv1Pos._x + 290, m_lv1Pos._y });
			break;
		default:
			break;
		}

		ServiceLocator::GetAudioSystem().AddAudio("Sound/die.WAV", 1, true);
	}
	if (InputManager::GetInstance().KeyUp("space"))
	{
		switch (m_selectedButton)
		{
		case Button::ButtonLevel1:
			ButtonClicked(Button::ButtonLevel1);
			break;
		case Button::ButtonLevel2:
			ButtonClicked(Button::ButtonLevel2);
			break;
		case Button::ButtonLevel3:
			ButtonClicked(Button::ButtonLevel3);
			break;
		case Button::ButtonVersus:
			ButtonClicked(Button::ButtonVersus);
			break;
		default:
			break;
		}
		
		ServiceLocator::GetAudioSystem().AddAudio("Sound/warp.WAV", 1, true);
	}
	
	Scene::Update();
}

void dae::TitleScreenScene::ButtonClicked(Button button)
{
	switch (button)
	{
	case Button::ButtonLevel1:
		dae::Game::SwitchLevel1();
		break;
	case Button::ButtonLevel2:
		dae::Game::SwitchLevel2();
		break;
	case Button::ButtonLevel3:
		dae::Game::SwitchLevel3();
		break;
	case Button::ButtonVersus:
		dae::Game::SwitchVersus();
		break;
	}
}