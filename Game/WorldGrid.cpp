#include "pch.h"
#include "WorldGrid.h"
#include "GridTile.h"

#include "EMath.h"
#include "Utils.h"
#include "Enums.h"

dae::WorldGrid::WorldGrid(std::vector<std::weak_ptr<GameObject>> gridTiles)
	: m_pGridTiles{ std::move(gridTiles) }
{
	m_pSubject = new Subject();
}

dae::WorldGrid::~WorldGrid()
{
	m_pSubject->DeleteAllObservers();
	if (m_pSubject != nullptr)
	{
		delete(m_pSubject);
		m_pSubject = nullptr;
	}
}

void dae::WorldGrid::AddObserver(Observer* observer) const
{
	m_pSubject->AddObserver(observer);
}

void dae::WorldGrid::RemoveObserver(Observer* observer) const
{
	m_pSubject->RemoveObserver(observer);
}

void dae::WorldGrid::Initialize()
{
}

void dae::WorldGrid::Update(float)
{	
	if (m_hasKilled)
	{
		m_pSubject->Notify(GetGameObject(), Event::Killed);
		m_hasKilled = false;
	}
	if (m_hasChangedTile)
	{
		m_pSubject->Notify(GetGameObject(), Event::TileChanged);
		m_hasChangedTile = false;
	}
	
	for (const auto& pTile : m_pGridTiles)
	{
		auto* tileInfo = pTile.lock()->GetComponent<GridTileInfo>();
		if (tileInfo != nullptr)
		{
			auto tile = tileInfo->GetTile();

			if (tile.GetTileState() != TileState::Wall)
			{
				Float2 center = tileInfo->GetTile().GetCenter();
				Elite::FPoint2 tileCenter = Elite::FPoint2(center._x, center._y);
				
				Elite::FVector2 pos = Elite::FVector2(GetGameObject()->GetPosition()._x, GetGameObject()->GetPosition()._y);
				pos.x += 20;
				pos.y -= 20;

				Elite::FPoint2 playerPos = Elite::FPoint2(pos);

				if (Elite::SqrDistance(tileCenter, playerPos) <= Elite::Square(m_MinDistance))
				{
					auto* pSpriteComponent = pTile.lock()->GetComponent<SpriteComponent>();
					pSpriteComponent->SetActiveAnimation("ChangedTile");

					m_hasChangedTile = true;
					tileInfo->GetTile().SetTileState(TileState::ChangedTile);
				}
			}		
		}
	}
}

void dae::WorldGrid::Render()
{
}
