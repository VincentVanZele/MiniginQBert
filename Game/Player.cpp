#include "pch.h"
#include "Player.h"

#include "GameObject.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "GameTime.h"
#include "ServiceLocator.h"
#include "GameCommands.h"
#include "GridTile.h"
#include "ScoreObserver.h"
#include "Subject.h"
#include "TransformComponent.h"

dae::Player::Player(GridTile* spawn)
	: m_pTexture(nullptr)
	, m_pSpawnTile(spawn)
	, m_pCurrentTile(spawn)
	, m_pSubject(new Subject())
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
	m_pSprite = new SpriteComponent();

	// Left
	auto tex = ServiceLocator::GetResourceManager()->GetInstance().LoadTexture("Q_BotLeft.png");
	auto sequence = std::make_shared<Animation>(tex, "Left", 2);
	m_pSprite->AddAnimation(sequence);

	// Idle
	tex = ServiceLocator::GetResourceManager()->GetInstance().LoadTexture("QBert.png");
	sequence = std::make_shared<Animation>(tex, "Idle", 2);
	m_pSprite->AddAnimation(sequence);

	// Right
	tex = ServiceLocator::GetResourceManager()->GetInstance().LoadTexture("Q_TopRight.png");
	sequence = std::make_shared<Animation>(tex, "Right", 2);
	m_pSprite->AddAnimation(sequence);

	// Up
	tex = ServiceLocator::GetResourceManager()->GetInstance().LoadTexture("Q_TopLeft.png");
	sequence = std::make_shared<Animation>(tex, "Up", 2);
	m_pSprite->AddAnimation(sequence);

	// Down
	tex = ServiceLocator::GetResourceManager()->GetInstance().LoadTexture("Q_BotRight.png");
	sequence = std::make_shared<Animation>(tex, "Down", 2);
	m_pSprite->AddAnimation(sequence);

	m_pSprite->SetActiveAnimation("Idle");

	this->AddComponent(m_pSprite);
	
	m_pTexture = ServiceLocator::GetResourceManager()->GetInstance().LoadTexture("QBert.png");
	
	// 0 -> first controller
	if (ServiceLocator::GetInputManager()->GetInstance().IsControllerConnected(0))
	{
		m_ControllerId = 0;
	}

	TeleportToTile(m_pSpawnTile);

	InputManager::GetInstance().AddCommand(new MoveUp(m_ControllerId, RequiredKeyState::KeyDown, this), ControllerButton::YVK);
	InputManager::GetInstance().AddCommand(new MoveDown(m_ControllerId, RequiredKeyState::KeyDown, this), ControllerButton::AVK);
	InputManager::GetInstance().AddCommand(new MoveLeft(m_ControllerId, RequiredKeyState::KeyDown, this), ControllerButton::XVK);
	InputManager::GetInstance().AddCommand(new MoveRight(m_ControllerId, RequiredKeyState::KeyDown, this), ControllerButton::BVK);
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
		m_pSubject->Notify(GameEvent::Died);
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
			if(m_pCurrentTile->GetTileState() == TileState::Disk)
			{
				TeleportToTile(m_pSpawnTile);
			}
			else if(m_pCurrentTile->GetTileState() == TileState::DeathPlane)
			{
				// die
				TeleportToTile(m_pSpawnTile);
			}
			
			m_needMoveUpdate = false;
			m_IsMoving = false;
			
			if(m_pCurrentTile->JumpedOn())
			{
				m_pSubject->Notify(GameEvent::TileChanged);
			}
			m_pCurrentTile->SetHasEntity(true);
			
			ToggleMoveRestriction();
		}
	}

	const Float2 animationPos = Float2
	{ this->GetTransform()->GetPosition()._x + (float)(m_pSprite->GetActiveAnimation().GetTexture().GetTextWidth() / 2.f),
		this->GetTransform()->GetPosition()._y - (float)(m_pSprite->GetActiveAnimation().GetTexture().GetTextHeight() / 2.f)
	};
	
	m_pSprite->GetActiveAnimation().SetPos(animationPos);
}

void dae::Player::Render()
{
	
}

void dae::Player::Die()
{
	TeleportToTile(m_pSpawnTile);
}


void dae::Player::MoveTo(TileConnections connection)
{
	if (m_pCurrentTile->HasConnectedTileAt(connection))
	{
		ToggleMoveRestriction();
		auto targetTile = m_pCurrentTile->GetConnectedTileAt(connection);
		if(targetTile == nullptr)
		{
			return;
		}

		m_pCurrentTile->SetHasEntity(false);
		
		m_pCurrentTile = targetTile;		
		m_TargetPosition = targetTile->GetCenter();

		m_IsMoving = true; // change texture
		
		UpdateTextures(connection);

		m_needMoveUpdate = true; // update
	}
}

void dae::Player::UpdateTextures(TileConnections state)
{
	auto resourceManager = ServiceLocator::GetResourceManager();
	
	// no need to check for nullptr, has been done in MoveTo
	switch (state)
	{
	case TileConnections::Default:
		m_pSprite->SetActiveAnimation("Idle");
		break;
	case TileConnections::Up: // Top left
		m_pSprite->SetActiveAnimation("Up");
		break;
	case TileConnections::Down: // Bot right
		m_pSprite->SetActiveAnimation("Down");
		break;
	case TileConnections::Left: // Bot left
		m_pSprite->SetActiveAnimation("Left");
		break;
	case TileConnections::Right: // Top right
		m_pSprite->SetActiveAnimation("Right");
		break;
	}
}

void dae::Player::TeleportToTile(GridTile* tile)
{
	if (tile == nullptr)
		return;

	m_pCurrentTile = tile;
	m_pCurrentTile->SetHasEntity(true);
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
