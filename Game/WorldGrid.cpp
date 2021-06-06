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

dae::WorldGrid::WorldGrid(GridType type, int width, Float2 pos, std::shared_ptr<GameObject> go)
	: m_gridPosition(pos)
	, m_size(width)
{
	m_pSubject = new Subject();

	// Rows
	for (int i = m_size; i != 0; i--)
	{
		// Reset tile position 
		m_tempPos = m_gridPosition;

		// Cols
		for (int j = 0; j < i; j++)
		{
			auto newTile = std::make_shared<GameObject>();
			newTile->AddComponent(new GridTile(type, m_tempPos));

			m_pGridTiles.push_back(newTile->GetComponent<GridTile>());

			// Outer Tiles
			if (i == m_size || j == 0 || j == i - 1)
			{
				m_pGridTiles.back()->SetTileState(TileState::DeathPlane);
				m_pGridTiles.back()->SetDefaultTileState(TileState::DeathPlane);
			}
			
			go->AddChild(newTile);
			m_tempPos._x += (float)newTile->GetComponent<GridTile>()->GetDefaultTexture()->GetTextWidth();
		}

		// Adapt tile to correct position
		m_gridPosition._x += (float)m_pGridTiles.back()->GetDefaultTexture()->GetTextWidth() / 2.f;
		m_gridPosition._y -= (float)m_pGridTiles.back()->GetDefaultTexture()->GetTextHeight() * 0.75f;
	}

/*
   idea discussed in public student feedback
   for(i=size)
	  for(j<i)
   reverse
 
	    First
	     /=\
	    /===\ 
	   /=====\
	  /=======\
    Last
*/
	std::reverse(m_pGridTiles.begin(), m_pGridTiles.end());

	// Adjacent tiles 
	for (int k = 0; k < (int)m_pGridTiles.size(); k++)
	{
		const int result = k * 2;
		
		const int vertical = result + m_offset;
		const int horizontal = result + m_offset + 1;
		
		m_counter++;

		if (m_counter != m_edge)
		{
			m_offset--;
		}
		else
		{
			m_counter = 0;
			m_edge++;
		}

		// Horizontal
		if (horizontal < (int)m_pGridTiles.size())
		{
			m_pGridTiles[k]->AddTileConnections(m_pGridTiles[horizontal], TileConnections::Left);
			m_pGridTiles[horizontal]->AddTileConnections(m_pGridTiles[k], TileConnections::Right);
		}
		// Vertical 
		if (vertical < (int)m_pGridTiles.size())
		{
			m_pGridTiles[k]->AddTileConnections(m_pGridTiles[vertical], TileConnections::Down);
			m_pGridTiles[vertical]->AddTileConnections(m_pGridTiles[k], TileConnections::Up);
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
	m_pGridTiles[m_disk1]->SetTileState(TileState::Disk);
	m_pGridTiles[m_disk1]->SetDefaultTileState(TileState::Disk);
	m_pSprite1->GetActiveAnimation().SetPos(Float2{ m_pGridTiles[m_disk1]->GetCenter()._x + m_diskOffset,m_pGridTiles[m_disk1]->GetCenter()._y + m_diskOffset });
	

	// Disk 2
	m_pSprite2 = new SpriteComponent();
	tex = ServiceLocator::GetResourceManager()->GetInstance().LoadTexture("Disk.png");
	sequence = std::make_shared<Animation>(tex, "Disk", 4);
	m_pSprite2->AddAnimation(sequence);
	m_pSprite2->SetActiveAnimation("Disk");
	
	// 28
	m_pGridTiles[m_disk2]->AddComponent(m_pSprite2);
	m_pGridTiles[m_disk2]->SetTileState(TileState::Disk);
	m_pGridTiles[m_disk2]->SetDefaultTileState(TileState::Disk);
	m_pSprite2->GetActiveAnimation().SetPos(Float2{ m_pGridTiles[m_disk2]->GetCenter()._x + m_diskOffset,m_pGridTiles[m_disk2]->GetCenter()._y + m_diskOffset });

	for (GridTile* grid : m_pGridTiles)
	{
		if(grid->GetTileState() == TileState::Tile)
		{
			m_pChangeableTiles.push_back(grid);
		}
	}
}

void dae::WorldGrid::Initialize()
{

}

void dae::WorldGrid::Render()
{

}

void dae::WorldGrid::Update()
{

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
