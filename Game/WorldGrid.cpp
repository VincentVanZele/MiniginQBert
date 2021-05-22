#include "pch.h"
#include "WorldGrid.h"
#include "GridTile.h"
#include "GameObject.h"

#include "EMath.h"
#include "Utils.h"
#include "Enums.h"

dae::WorldGrid::WorldGrid(int width, Float2 pos)
	: m_width(width)
	, m_gridPosition(pos)
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

void dae::WorldGrid::Initialize()
{
	Float2 tempPos = m_gridPosition;
	int leftChild{}, rightChild{};
	int offset{ 1 }, endOfLine{ 1 }, counter{ 0 };

	// Rows
	for (int i = m_width; i != 0; i--)
	{
		// Reset tile position 
		tempPos = m_gridPosition;

		// Cols
		for (int j = 0; j < i; j++)
		{
			auto *newTile = new GameObject();
			newTile->AddComponent(new GridTile(tempPos));
			
			m_pGridTiles.push_back(newTile->GetComponent<GridTile>());

			// Edge cases
			if (i == m_width)
			{
				m_pGridTiles.back()->SetEdgeCaseRow(true);
			}
			if (j == 0 || j == i - 1)
			{
				m_pGridTiles.back()->SetEdgeCaseCol(true);
			}

			m_pGameObject->AddChild(newTile);
			tempPos._x += (float)newTile->GetComponent<GridTile>()->GetDefaultTexture()->GetTextWidth();
		}

		// Adapt tile position
		m_gridPosition._x += m_pGridTiles.back()->GetDefaultTexture()->GetTextWidth() / 2;
		m_gridPosition._y -= m_pGridTiles.back()->GetDefaultTexture()->GetTextHeight() * 0.75f;
	}
	std::reverse(m_pGridTiles.begin(), m_pGridTiles.end());

	// Adjacent tiles 
	for (int i = 0; i < (int)m_pGridTiles.size(); i++)
	{
		rightChild = i * 2 + offset;
		leftChild = i * 2 + offset + 1;
		counter++;

		if (counter != endOfLine)
		{
			offset--;
		}
		else
		{
			counter = 0;
			endOfLine++;
		}

		// Vertical 
		if (rightChild < m_pGridTiles.size())
		{
			m_pGridTiles[i]->AddTileConnections(m_pGridTiles[rightChild], TileConnections::Down);
			m_pGridTiles[rightChild]->AddTileConnections(m_pGridTiles[i], TileConnections::Up);
		}

		// Horizontal
		if (leftChild < m_pGridTiles.size())
		{
			m_pGridTiles[i]->AddTileConnections(m_pGridTiles[leftChild], TileConnections::Left);
			m_pGridTiles[leftChild]->AddTileConnections(m_pGridTiles[i], TileConnections::Right);
		}
		
	}
}

int dae::WorldGrid::GetCubeIndex(GridTile* tile) const
{
	for (int i{}; i < (int)m_pGridTiles.size(); i++)
	{
		if (m_pGridTiles[i] == tile)
		{
			return i;
		}
	}
	return -1;
}

dae::GridTile* dae::WorldGrid::GetCubeAtIndex(int ) const
{
	return m_pGridTiles.front();
}

void dae::WorldGrid::AddObserver(Observer* observer) const
{
	m_pSubject->AddObserver(observer);
}

void dae::WorldGrid::RemoveObserver(Observer* observer) const
{
	m_pSubject->RemoveObserver(observer);
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
	
	/*for (const auto& pTile : m_pGridTiles)
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
	}*/
}

void dae::WorldGrid::Render()
{

}