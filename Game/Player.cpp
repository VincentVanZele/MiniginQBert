#include "pch.h"
#include "Player.h"
#include <iostream>

#include "InputManager.h"
#include "ServiceLocator.h"
#include "GameCommands.h"
#include "GridTile.h"
#include "Subject.h"

dae::Player::Player(PlayerIndex player)
	: m_PlayerNumber{ player }
	, m_pTexture(nullptr)
	, m_pCurrentTile(nullptr)
{
}

dae::Player::~Player()
{
	delete m_pActivState;
	m_pActivState = nullptr;
	m_pSprite = nullptr;
}

void dae::Player::Initialize()
{
	m_pSprite = m_pGameObject->GetComponent<SpriteComponent>();

	switch (m_PlayerNumber)
	{
	case PlayerIndex::PlayerOne:
		// 0 -> first controller
		if (ServiceLocator::GetInputManager()->GetInstance().IsControllerConnected(0))
		{
			m_ControllerId = 0;
			break;
		}
	case PlayerIndex::PlayerTwo:
		// 1 -> second controller  
		if (ServiceLocator::GetInputManager()->GetInstance().IsControllerConnected(1))
		{
			m_ControllerId = 1;
			break;
		}
	}

	InputManager::GetInstance().AddCommand(new MoveUp(m_ControllerId, RequiredKeyState::KeyDown, GetGameObject()), ControllerButton::DpadUpVK);
	InputManager::GetInstance().AddCommand(new MoveDown(m_ControllerId, RequiredKeyState::KeyDown, GetGameObject()), ControllerButton::DpadDownVK);
	InputManager::GetInstance().AddCommand(new MoveLeft(m_ControllerId, RequiredKeyState::KeyDown, GetGameObject()), ControllerButton::DpadLeftVK);
	InputManager::GetInstance().AddCommand(new MoveRight(m_ControllerId, RequiredKeyState::KeyDown, GetGameObject()), ControllerButton::DpadRightVK);
}

void dae::Player::Update(float deltaTime)
{
	if (m_pActivState != nullptr)
	{
		ActorState* newState = m_pActivState->Update(deltaTime);
		if (newState != nullptr)
		{
			m_pActivState->ExitState();
			delete m_pActivState;
			m_pActivState = newState;
			m_pActivState->EnterState();
		}
	}
	m_Input = Input::Default;

	if (m_hasDied)
	{
		--m_lives;
		m_pSubject->Notify(GetGameObject(), Event::Died);
		m_hasDied = false;
	}
}

void dae::Player::Render()
{
}

void dae::Player::ToTile(GridTile* tile)
{
	if (tile == nullptr)
		return;

	m_pCurrentTile = tile;
	m_pGameObject->SetPosition(m_pCurrentTile->GetCenter()._x, m_pCurrentTile->GetCenter()._y);
}


void dae::Player::AddObserver(Observer* observer)
{
	m_pSubject->AddObserver(observer);
}

void dae::Player::RemoveObserver(Observer* observer)
{
	m_pSubject->RemoveObserver(observer);
}
