#include "pch.h"
#include "Player.h"
#include <iostream>

#include "GameObject.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "GameTime.h"
#include "ServiceLocator.h"
#include "GameCommands.h"
#include "GridTile.h"
#include "Subject.h"
#include "TransformComponent.h"

dae::Player::Player()
	: m_pTexture(nullptr)
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
	m_pSprite = m_pGameObject.lock()->GetComponent<SpriteComponent>();
	m_pTexture = ServiceLocator::GetResourceManager()->GetInstance().LoadTexture("QBert.png");
	
	// 0 -> first controller
	if (ServiceLocator::GetInputManager()->GetInstance().IsControllerConnected(0))
	{
		m_ControllerId = 0;
	}

	InputManager::GetInstance().AddCommand(new MoveUp(m_ControllerId, RequiredKeyState::KeyDown, this), ControllerButton::DpadUpVK);
	InputManager::GetInstance().AddCommand(new MoveDown(m_ControllerId, RequiredKeyState::KeyDown, this), ControllerButton::DpadDownVK);
	InputManager::GetInstance().AddCommand(new MoveLeft(m_ControllerId, RequiredKeyState::KeyDown, this), ControllerButton::DpadLeftVK);
	InputManager::GetInstance().AddCommand(new MoveRight(m_ControllerId, RequiredKeyState::KeyDown, this), ControllerButton::DpadRightVK);
}

void dae::Player::Update()
{
	if (m_pActivState != nullptr)
	{
		ActorState* newState = m_pActivState->Update();
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

	if(m_needMoveUpdate)
	{
		auto x = m_TargetPosition._x - m_pGameObject.lock()->GetTransform()->GetPosition()._x;
		auto y = m_TargetPosition._y - m_pGameObject.lock()->GetTransform()->GetPosition()._y;

		Float3 vectDir = Float3{ x, y, 0 };
		vectDir = vectDir.Normalize();

		const Float3 result = Float3{ m_pGameObject.lock()->GetTransform()->GetPosition()._x,m_pGameObject.lock()->GetTransform()->GetPosition()._y,0 } + vectDir * m_WalkSpeed * ServiceLocator::GetGameTime()->GetInstance().GetDeltaTime();
		
		m_pGameObject.lock()->GetTransform()->SetPosition(Float2{ result._x,result._y });

		const Float2 lengthResult = Float2{ x,y };
		if (lengthResult.Length() <= 2.f)
		{
			m_needMoveUpdate = false;
		}
	}
}

void dae::Player::Render()
{
	// Texture
	if (m_pTexture != nullptr)
	{
		const auto goPos = m_pGameObject.lock()->GetTransform()->GetPosition();
		Renderer::GetInstance().RenderTexture(*m_pTexture, goPos._x, goPos._y);
	}
}

void dae::Player::MoveTo(TileConnections connection)
{
	if (m_pCurrentTile->HasConnectedTileAt(connection))
	{
		auto targetTile = m_pCurrentTile->GetConnectedTileAt(connection);
		if(targetTile == nullptr)
		{
			return;
		}

		m_pCurrentTile = targetTile;

		m_IsMoving = true; // change texture
		m_TargetPosition = targetTile->GetCenter();
		
	}

	// Modify 
	UpdateTextures(connection);
}

void dae::Player::UpdateTextures(TileConnections state)
{
	auto resourceManager = ServiceLocator::GetResourceManager();
	
	// no need to check for nullptr, has been done in MoveTo
	switch (state)
	{
	case TileConnections::Up: // Top left
		m_pTexture = resourceManager->GetInstance().LoadTexture("Q_TopLeft.png");
		break;
	case TileConnections::Down: // Bot right
		m_pTexture = resourceManager->GetInstance().LoadTexture("Q_BotRight.png");
		break;
	case TileConnections::Left: // Bot left
		m_pTexture = resourceManager->GetInstance().LoadTexture("Q_BotLeft.png");
		break;
	case TileConnections::Right: // Top right
		m_pTexture = resourceManager->GetInstance().LoadTexture("Q_TopRight.png");
		break;
	}
}

void dae::Player::SetBaseTile(GridTile* tile)
{
	if (tile == nullptr)
		return;

	m_pCurrentTile = tile;
	// TP
	m_pGameObject.lock()->GetTransform()->SetPosition(Float2{ m_pCurrentTile->GetCenter()._x, m_pCurrentTile->GetCenter()._y });
}

void dae::Player::AddObserver(Observer* observer) const 
{
	m_pSubject->AddObserver(observer);
}

void dae::Player::RemoveObserver(Observer* observer) const 
{
	m_pSubject->RemoveObserver(observer);
}
