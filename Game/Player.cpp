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

dae::Player::Player(GridTile* spawn, PlayerIdx idx)
	: m_pTexture(nullptr)
	, m_pCurrentTile(spawn)
	, m_pSubject(new Subject())
	, m_player(idx)
	, m_pSpawnTile(spawn)
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
	if(m_player == PlayerIdx::Player1)
	{
		Player1();
	}
	else
	{
		Player2();
	}
}

void dae::Player::Player1()
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

void dae::Player::Player2()
{
	m_pSprite = new SpriteComponent();

	// Left
	auto tex = ServiceLocator::GetResourceManager()->GetInstance().LoadTexture("Q2_BotLeft.png");
	auto sequence = std::make_shared<Animation>(tex, "Left2", 2);
	m_pSprite->AddAnimation(sequence);

	// Idle
	tex = ServiceLocator::GetResourceManager()->GetInstance().LoadTexture("QBert2.png");
	sequence = std::make_shared<Animation>(tex, "Idle2", 2);
	m_pSprite->AddAnimation(sequence);

	// Right
	tex = ServiceLocator::GetResourceManager()->GetInstance().LoadTexture("Q2_TopRight.png");
	sequence = std::make_shared<Animation>(tex, "Right2", 2);
	m_pSprite->AddAnimation(sequence);

	// Up
	tex = ServiceLocator::GetResourceManager()->GetInstance().LoadTexture("Q2_TopLeft.png");
	sequence = std::make_shared<Animation>(tex, "Up2", 2);
	m_pSprite->AddAnimation(sequence);

	// Down
	tex = ServiceLocator::GetResourceManager()->GetInstance().LoadTexture("Q2_BotRight.png");
	sequence = std::make_shared<Animation>(tex, "Down2", 2);
	m_pSprite->AddAnimation(sequence);

	m_pSprite->SetActiveAnimation("Idle2");

	this->AddComponent(m_pSprite);

	m_pTexture = ServiceLocator::GetResourceManager()->GetInstance().LoadTexture("QBert2.png");


	TeleportToTile(m_pSpawnTile);

	InputManager::GetInstance().AddInput("left", 'a');
	InputManager::GetInstance().AddInput("right", 'e');
	InputManager::GetInstance().AddInput("up", 'q');
	InputManager::GetInstance().AddInput("down", 'd');
}

void dae::Player::Update()
{
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
				Die();
			}
			
			m_needMoveUpdate = false;
			m_IsMoving = false;
			
			if(m_pCurrentTile->JumpedOn(m_player))
			{
				m_pSubject->Notify(GameEvent::TileChanged);
			}
			
			ToggleMoveRestriction();
		}
	}

	if (m_pCurrentTile->GetGridType() != GridType::Versus)
	{
		if (m_pCurrentTile->GetHasEntity())
		{
			Die();
		}
	}

	const Float2 animationPos = Float2
	{ this->GetTransform()->GetPosition()._x + (float)(m_pSprite->GetActiveAnimation().GetTexture().GetTextWidth() / 2.f),
		this->GetTransform()->GetPosition()._y - (float)(m_pSprite->GetActiveAnimation().GetTexture().GetTextHeight() / 2.f)
	};
	
	m_pSprite->GetActiveAnimation().SetPos(animationPos);

	if(m_player==PlayerIdx::Player2)
	{
		HandleKeyboardInput();
	}
}

void dae::Player::Render()
{
	
}

void dae::Player::Die()
{
	TeleportToTile(m_pSpawnTile);
	m_pSubject->Notify(GameEvent::Died);
}

void dae::Player::HandleKeyboardInput()
{
	if (InputManager::GetInstance().KeyUp("left") && !m_moveRestriction)
	{
		this->MoveTo(TileConnections::Left);
	}
	if (InputManager::GetInstance().KeyUp("right") && !m_moveRestriction)
	{
		this->MoveTo(TileConnections::Right);
	}
	if (InputManager::GetInstance().KeyUp("up") && !m_moveRestriction)
	{
		this->MoveTo(TileConnections::Up);
	}
	if (InputManager::GetInstance().KeyUp("down") && !m_moveRestriction)
	{
		this->MoveTo(TileConnections::Down);
	}
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
	if (m_player == PlayerIdx::Player1)
	{
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
	else
	{
		switch (state)
		{
		case TileConnections::Default:
			m_pSprite->SetActiveAnimation("Idle2");
			break;
		case TileConnections::Up: // Top left
			m_pSprite->SetActiveAnimation("Up2");
			break;
		case TileConnections::Down: // Bot right
			m_pSprite->SetActiveAnimation("Down2");
			break;
		case TileConnections::Left: // Bot left
			m_pSprite->SetActiveAnimation("Left2");
			break;
		case TileConnections::Right: // Top right
			m_pSprite->SetActiveAnimation("Right2");
			break;
		}
	}
}

void dae::Player::TeleportToTile(GridTile* tile)
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
