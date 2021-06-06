#include "pch.h"
#include "Enemy.h"

#include "SpriteComponent.h"
#include "Animation.h"
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

dae::Enemy::Enemy(GridTile* spawn)
	: m_pSubject(new Subject())
	, m_pCurrentTile(spawn)
	, m_pSpawnTile(spawn)
{

}

dae::Enemy::~Enemy()
{
	m_pSprite = nullptr;
}


void dae::Enemy::Initialize()
{
	m_pSprite = new SpriteComponent();

	// Left
	auto tex = ServiceLocator::GetResourceManager()->GetInstance().LoadTexture("S_BotLeft.png");
	auto sequence = std::make_shared<Animation>(tex, "SLeft", 2);
	m_pSprite->AddAnimation(sequence);

	// Right
	tex = ServiceLocator::GetResourceManager()->GetInstance().LoadTexture("S_TopRight.png");
	sequence = std::make_shared<Animation>(tex, "SRight", 2);
	m_pSprite->AddAnimation(sequence);

	// Up
	tex = ServiceLocator::GetResourceManager()->GetInstance().LoadTexture("S_TopLeft.png");
	sequence = std::make_shared<Animation>(tex, "SUp", 2);
	m_pSprite->AddAnimation(sequence);

	// Down
	tex = ServiceLocator::GetResourceManager()->GetInstance().LoadTexture("S_BotRight.png");
	sequence = std::make_shared<Animation>(tex, "SDown", 2);
	m_pSprite->AddAnimation(sequence);

	m_pSprite->SetActiveAnimation("SLeft");

	this->AddComponent(m_pSprite);

	TeleportToTile(m_pSpawnTile);
}

void dae::Enemy::Update()
{
	if(m_needDirection)
	{
		m_waitTimer += ServiceLocator::GetGameTime()->GetInstance().GetDeltaTime();

		if (m_waitTimer > 1)
		{
			const int rando = rand() % 4;
			switch (rando)
			{
			case 0:
				MoveTo(TileConnections::Up);
				m_needDirection = false;
				break;
			case 1:
				MoveTo(TileConnections::Down);
				m_needDirection = false;
				break;
			case 2:
				MoveTo(TileConnections::Left);
				m_needDirection = false;
				break;
			case 3:
				MoveTo(TileConnections::Right);
				m_needDirection = false;
				break;
			}
			m_waitTimer = 0;
		}
	}
	
	if (m_needMoveUpdate)
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
			if (m_pCurrentTile->GetTileState() == TileState::Disk)
			{
				TeleportToTile(m_pSpawnTile);
			}
			else if (m_pCurrentTile->GetTileState() == TileState::DeathPlane)
			{
				// die
				TeleportToTile(m_pSpawnTile);
			}

			m_needMoveUpdate = false;
			m_IsMoving = false;
			m_pCurrentTile->SetHasEntity(true);

			
			ToggleMoveRestriction();
			m_needDirection = true;
		}
	}

	const Float2 animationPos = Float2
	{ this->GetTransform()->GetPosition()._x + (float)(m_pSprite->GetActiveAnimation().GetTexture().GetTextWidth() / 2.f),
		this->GetTransform()->GetPosition()._y - (float)(m_pSprite->GetActiveAnimation().GetTexture().GetTextHeight() / 2.f)
	};

	m_pSprite->GetActiveAnimation().SetPos(animationPos);
}

void dae::Enemy::Render()
{

}

void dae::Enemy::Die()
{
	TeleportToTile(m_pSpawnTile);
}

void dae::Enemy::MoveTo(TileConnections connection)
{
	if (m_pCurrentTile->HasConnectedTileAt(connection))
	{
		ToggleMoveRestriction();
		auto targetTile = m_pCurrentTile->GetConnectedTileAt(connection);
		if (targetTile == nullptr)
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

void dae::Enemy::UpdateTextures(TileConnections state)
{
	auto resourceManager = ServiceLocator::GetResourceManager();

	switch (state)
	{
	case TileConnections::Default:
		m_pSprite->SetActiveAnimation("SIdle");
		break;
	case TileConnections::Up: // Top left
		m_pSprite->SetActiveAnimation("SUp");
		break;
	case TileConnections::Down: // Bot right
		m_pSprite->SetActiveAnimation("SDown");
		break;
	case TileConnections::Left: // Bot left
		m_pSprite->SetActiveAnimation("SLeft");
		break;
	case TileConnections::Right: // Top right
		m_pSprite->SetActiveAnimation("SRight");
		break;
	}
}

void dae::Enemy::TeleportToTile(GridTile* tile)
{
	if (tile == nullptr)
		return;

	m_pCurrentTile = tile;
	m_pCurrentTile->SetHasEntity(true);
	// TP
	m_pGameObject.lock()->GetTransform()->SetPosition(Float2{ m_pCurrentTile->GetCenter()._x, m_pCurrentTile->GetCenter()._y });
}

void dae::Enemy::AddObserver(Observer* observer) const
{
	m_pSubject->AddObserver(observer);
}

void dae::Enemy::RemoveObserver(Observer* observer) const
{
	m_pSubject->RemoveObserver(observer);
}
