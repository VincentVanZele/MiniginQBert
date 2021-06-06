#include "pch.h"
#include "Eggs.h"

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
#include "AudioSystem.h"

dae::Eggs::Eggs(GridTile* base, EggType type, Float2 spawn, bool delayed)
	: m_pBaseTile(base)
	, m_SpawnPos(spawn)
	, m_eggType(type)
	, m_isDelayed(delayed)
{
}

void dae::Eggs::Initialize()
{
	m_pSprite = new SpriteComponent();

	switch (m_eggType)
	{
	case EggType::Green:
	{
		auto tex = ServiceLocator::GetResourceManager()->GetInstance().LoadTexture("Egg_Green.png");
		auto sequence = std::make_shared<Animation>(tex, "GEgg", 2);
		m_pSprite->AddAnimation(sequence);
		m_pSprite->SetActiveAnimation("GEgg");

		break;
	}
	case EggType::Purple:
	{
		auto tex = ServiceLocator::GetResourceManager()->GetInstance().LoadTexture("Egg_Purple.png");
		auto sequence = std::make_shared<Animation>(tex, "PEgg", 2);
		m_pSprite->AddAnimation(sequence);
		m_pSprite->SetActiveAnimation("PEgg");

		break;
	}
	case EggType::Red:
	{
		auto tex = ServiceLocator::GetResourceManager()->GetInstance().LoadTexture("Egg_Red.png");
		auto sequence = std::make_shared<Animation>(tex, "REgg", 2);
		m_pSprite->AddAnimation(sequence);
		m_pSprite->SetActiveAnimation("REgg");

		break;
	}
	}

	m_pGameObject.lock()->GetTransform()->SetPosition(m_SpawnPos);

	this->AddComponent(m_pSprite);
	const Float2 animationPos = Float2
	{ this->GetTransform()->GetPosition()._x + (float)(m_pSprite->GetActiveAnimation().GetTexture().GetTextWidth() / 2.f),
		this->GetTransform()->GetPosition()._y - (float)(m_pSprite->GetActiveAnimation().GetTexture().GetTextHeight() / 2.f)
	};

	m_pSprite->GetActiveAnimation().SetPos(animationPos);
	
	MoveToTile(m_pBaseTile);
}

dae::Eggs::~Eggs()
{
	m_pSprite = nullptr;
}

void dae::Eggs::Update()
{
	if(m_isDelayed)
	{
		// countdown
		m_elapsedTime += ServiceLocator::GetGameTime()->GetInstance().GetDeltaTime();
		if (m_elapsedTime < m_delay)
			return;
		m_isDelayed = false;
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
			m_goLeft = !m_goLeft;
			m_IsMoving = false;
			m_pCurrentTile->SetHasEntity(true);

			m_waitTimer += ServiceLocator::GetGameTime()->GetInstance().GetDeltaTime();

			if (m_waitTimer > 1)
			{
				ServiceLocator::GetAudioSystem().AddAudio("Sound/blob.WAV", 1, true);
				m_waitTimer = 0;
				if (m_pCurrentTile->GetTileState() != TileState::DeathPlane)
				{
					if (m_goLeft)
					{
						MoveTo(TileConnections::Left);
					}
					else
					{
						MoveTo(TileConnections::Down);
					}
				}
				else
				{
					m_pGameObject.lock()->GetTransform()->SetPosition(m_SpawnPos);
					m_pCurrentTile->SetHasEntity(false);
					m_pCurrentTile = m_pBaseTile;
					m_TargetPosition = m_pBaseTile->GetCenter();
				}
			}		
		}
	}

	const Float2 animationPos = Float2
	{ this->GetTransform()->GetPosition()._x + (float)(m_pSprite->GetActiveAnimation().GetTexture().GetTextWidth() / 2.f),
		this->GetTransform()->GetPosition()._y - (float)(m_pSprite->GetActiveAnimation().GetTexture().GetTextHeight() / 2.f)
	};

	m_pSprite->GetActiveAnimation().SetPos(animationPos);
}

void dae::Eggs::Render()
{
	
}

void dae::Eggs::MoveTo(TileConnections connection)
{
	if (m_pCurrentTile->HasConnectedTileAt(connection))
	{
		auto targetTile = m_pCurrentTile->GetConnectedTileAt(connection);
		if (targetTile == nullptr)
		{
			return;
		}

		m_pCurrentTile->SetHasEntity(false);

		m_pCurrentTile = targetTile;
		m_TargetPosition = targetTile->GetCenter();
	}
}

void dae::Eggs::MoveToTile(GridTile* tile)
{
	// Used once at start of game 
	if (tile != nullptr)
	{
		m_pCurrentTile = tile;
		m_TargetPosition = tile->GetCenter();
		m_needMoveUpdate = true; // update
	}
}