#include "pch.h"
#include "WorldGrid.h"
#include "GridTile.h"
#include "GameObject.h"

#include "ServiceLocator.h"
#include "ResourceManager.h"
#include "Animation.h"
#include "SpriteComponent.h"

#include "EMath.h"
#include "Utils.h"
#include "Enums.h"

dae::WorldGrid::WorldGrid(int width, Float2 pos, std::shared_ptr<GameObject> go)
	: m_width(width)
	, m_gridPosition(pos)
{
	m_pSubject = new Subject();

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
			auto newTile = std::make_shared<GameObject>();
			newTile->AddComponent(new GridTile(tempPos));

			m_pGridTiles.push_back(newTile->GetComponent<GridTile>());

			// Edge cases
			if (i == m_width)
			{
				m_pGridTiles.back()->SetEdgeCaseRow(true);
				m_pGridTiles.back()->SetTileState(TileState::DeathPlane);
			}
			if (j == 0 || j == i - 1)
			{
				m_pGridTiles.back()->SetEdgeCaseCol(true);
				m_pGridTiles.back()->SetTileState(TileState::DeathPlane);
			}
			
			go->AddChild(newTile);
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

	// Disk 1
	m_pSprite1 = new SpriteComponent();
	auto tex = ServiceLocator::GetResourceManager()->GetInstance().LoadTexture("Disk.png");
	auto sequence = std::make_shared<Animation>(tex, "Disk", 4);
	m_pSprite1->AddAnimation(sequence);
	m_pSprite1->SetActiveAnimation("Disk");

	// special cases 22
	m_pGridTiles[m_disk1]->AddComponent(m_pSprite1);
	m_pSprite1->GetActiveAnimation().SetPos(Float2{ m_pGridTiles[m_disk1]->GetCenter()._x + tex->GetTextWidth() - m_diskOffset,m_pGridTiles[m_disk1]->GetCenter()._y + m_diskOffset });
	

	// Disk 2
	m_pSprite2 = new SpriteComponent();
	tex = ServiceLocator::GetResourceManager()->GetInstance().LoadTexture("Disk.png");
	sequence = std::make_shared<Animation>(tex, "Disk", 4);
	m_pSprite2->AddAnimation(sequence);
	m_pSprite2->SetActiveAnimation("Disk");
	
	// 28
	m_pGridTiles[m_disk2]->AddComponent(m_pSprite2);
	m_pSprite2->GetActiveAnimation().SetPos(Float2{ m_pGridTiles[m_disk2]->GetCenter()._x + m_diskOffset,m_pGridTiles[m_disk2]->GetCenter()._y + m_diskOffset });

	for (GridTile* grid : m_pGridTiles)
	{
		if(grid->GetTileState() == TileState::Tile)
		{
			m_pChangeableTiles.push_back(grid);
		}
	}
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

dae::GridTile* dae::WorldGrid::GetFrontCube() const
{
	return m_pGridTiles.front();
}

dae::GridTile* dae::WorldGrid::GetCubeAtIndex(int idx) const
{
	return m_pGridTiles[idx];
}

void dae::WorldGrid::AddObserver(Observer* observer) const
{
	m_pSubject->AddObserver(observer);
}

void dae::WorldGrid::RemoveObserver(Observer* observer) const
{
	m_pSubject->RemoveObserver(observer);
}

void dae::WorldGrid::Update()
{	

}

void dae::WorldGrid::Render()
{

}