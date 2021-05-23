#include "pch.h"
#include "GridTile.h"

#include "ResourceManager.h"
#include "Renderer.h"
#include "ServiceLocator.h"

dae::GridTile::GridTile(Float2 center)
	: m_tileCenter(center)
	, m_pAdjacentTiles{ nullptr }
{
	auto resourceManager = ServiceLocator::GetResourceManager();

	m_pTextDefault = resourceManager->GetInstance().LoadTexture("DefaultTile.png");
	m_pTextChanged = resourceManager->GetInstance().LoadTexture("ChangedTile.png");
}

void dae::GridTile::Initialize()
{
	
}

void dae::GridTile::Update( )
{
	/*auto renderer = ServiceLocator::GetRenderer();
	
	if (m_NeedUpdate)
	{
		auto resourceManager = ServiceLocator::GetResourceManager();
		
		if (m_state == TileState::Tile)
		{
			m_pTextDefault = resourceManager->GetInstance().LoadTexture("Qube.png");
		}
		else
		{
			renderer->GetInstance().RenderTexture(*m_pTextChanged, m_tileCenter._x, m_tileCenter._y);
		}
	}*/
}

void dae::GridTile::Render()
{
	if (m_pTextDefault != nullptr)
	{
		Renderer::GetInstance().RenderTexture(*m_pTextDefault, m_tileCenter._x, m_tileCenter._y);
	}
}

void dae::GridTile::AddTileConnections(GridTile* tileToLink, TileConnections connection)
{
	const int tileConnection = (int)connection;
	m_pAdjacentTiles[tileConnection] = tileToLink;
}
