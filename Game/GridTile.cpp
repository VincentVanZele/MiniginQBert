#include "pch.h"
#include "GridTile.h"

#include "SpriteComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "ServiceLocator.h"

dae::GridTile::GridTile(GridType type, Float2 center)
	: m_tileCenter(center)
	, m_gridType(type)
	, m_pAdjacentTiles{ nullptr }
{
	auto resourceManager = ServiceLocator::GetResourceManager();

	switch (m_gridType)
	{
	case GridType::Base:
		m_pTextDefault = resourceManager->GetInstance().LoadTexture("DefaultTile.png");
		m_pTextChanged = resourceManager->GetInstance().LoadTexture("ChangedTile.png");
		
		break;
	case GridType::TwoJumps:
		m_pTextDefault = resourceManager->GetInstance().LoadTexture("DefaultTile2.png");
		m_pTextChanged = resourceManager->GetInstance().LoadTexture("ChangedTile2.png");
		m_pTextIntermediate = resourceManager->GetInstance().LoadTexture("IntermediateTile2.png");

		break;
	case GridType::Reset:
		m_pTextDefault = resourceManager->GetInstance().LoadTexture("DefaultTile3.png");
		m_pTextChanged = resourceManager->GetInstance().LoadTexture("ChangedTile3.png");

		break;
	case GridType::Versus:
		m_pTextDefault = resourceManager->GetInstance().LoadTexture("DefaultTile.png");
		m_pTextChanged = resourceManager->GetInstance().LoadTexture("ChangedTile.png");
		m_pAltTextChanged = resourceManager->GetInstance().LoadTexture("AltChangedTile.png");
		
		break;
	}
}

void dae::GridTile::Initialize()
{
	
}

void dae::GridTile::Update( )
{
	
}

bool dae::GridTile::JumpedOn(int playerId)
{
	switch (m_gridType)
	{
	case GridType::Base:

		if(m_state == TileState::Tile)
		{
			m_state = TileState::ChangedTile;
			return true;
		}
		
		break;
	case GridType::TwoJumps:

		if (m_state != TileState::ChangedTile)
		{
			if (m_canChange)
			{
				if (m_state == TileState::Intermediate)
				{
					m_state = TileState::ChangedTile;
					return true;
				}
			}

			m_canChange = true;
			m_state = TileState::Intermediate;
		}
		
		break;
	case GridType::Reset:
		if (m_state == TileState::Tile)
		{
			m_state = TileState::ChangedTile;
		}
		else if (m_state == TileState::ChangedTile)
		{
			m_state = TileState::Tile;
		}
		break;
	case GridType::Versus:
		switch (playerId)
		{
		case 0:
			m_state = TileState::ChangedTile;
			break;
		case 1:
			m_state = TileState::AltChangedTile;
			break;
		default:
			break;
		}
		break;
	}
	return false;
}

void dae::GridTile::Reset()
{
	m_state = m_defaultState;
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
		if (m_pTextIntermediate != nullptr)
		{
			Renderer::GetInstance().RenderTexture(*m_pTextIntermediate, m_tileCenter._x, m_tileCenter._y);
		}
		break;
	case TileState::ChangedTile:
		if (m_pTextChanged != nullptr)
		{
			Renderer::GetInstance().RenderTexture(*m_pTextChanged, m_tileCenter._x, m_tileCenter._y);
		}
		break;
	case TileState::AltChangedTile:
		if (m_pTextChanged != nullptr)
		{
			Renderer::GetInstance().RenderTexture(*m_pAltTextChanged, m_tileCenter._x, m_tileCenter._y);
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
