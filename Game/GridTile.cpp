#include "pch.h"
#include "GridTile.h"

#include "GameObject.h"
#include "SpriteComponent.h"
#include "Animation.h"
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
	m_pTextDeath = resourceManager->GetInstance().LoadTexture("Death.png");
}

void dae::GridTile::Initialize()
{
	
}

void dae::GridTile::Update( )
{
	
}

void dae::GridTile::Render()
{
	switch(m_state)
	{
	case TileState::Tile:
		if (m_pTextDefault != nullptr)
		{
			Renderer::GetInstance().RenderTexture(*m_pTextDefault, m_tileCenter._x, m_tileCenter._y);
		}
		break;
	case TileState::Intermediate:

		break;
	case TileState::ChangedTile:
		if (m_pTextChanged != nullptr)
		{
			Renderer::GetInstance().RenderTexture(*m_pTextChanged, m_tileCenter._x, m_tileCenter._y);
		}
		break;
	case TileState::Disk:
		// handled elsewhere
		break;
	case TileState::DeathPlane:
		// nothing
		break;
	}

}

void dae::GridTile::AddTileConnections(GridTile* tileToLink, TileConnections connection)
{
	const int tileConnection = (int)connection;
	m_pAdjacentTiles[tileConnection] = tileToLink;
}
