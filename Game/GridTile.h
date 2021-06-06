#pragma once
#include "BaseComponent.h"
#include "Texture2D.h"
#include <array>
#include <Structs.h>

namespace dae
{
	class SpriteComponent;

	enum class GridType
	{
		Base, TwoJumps, Reset, Versus
	};
	
	enum TileState
	{
		Disk, Tile, Intermediate, ChangedTile, AltChangedTile, DeathPlane
	};

	enum class TileConnections
	{
		Up, Down, Left, Right, Default
	};

	class GridTile : public BaseComponent
	{
	public:
		GridTile(GridType type, Float2 center);
		~GridTile() override = default;

		GridTile(const GridTile& other) = delete;
		GridTile(GridTile&& other) noexcept = delete;
		GridTile& operator=(const GridTile& other) = delete;
		GridTile& operator=(GridTile&& other) noexcept = delete;

		void Initialize() override;
		void Update() override;
		void Render() override;

		bool JumpedOn(int playerId);
		
		void Reset();

		void AddTileConnections(GridTile* tileToLink, TileConnections connection);
		std::array<GridTile*, 4> GetTileConnections() const
		{
			return m_pAdjacentTiles;
		}

		bool HasConnectedTileAt(TileConnections dir) const
		{
			if (m_pAdjacentTiles.at((int)dir) != nullptr)
			{
				return true;
			}
			return false;
		};

		GridTile* GetConnectedTileAt(TileConnections dir) const
		{
			return m_pAdjacentTiles.at((int)dir);
		};
		
		Float2 GetCenter() const
		{
			return m_tileCenter;
		}
		void SetCenter(Float2 center)
		{
			m_tileCenter = center;
		}

		bool ToggleState()
		{
			if (m_state == Tile)
			{
				m_state = ChangedTile;
				return true;
			}
			return false;
		}
		TileState GetTileState() const
		{
			return m_state;
		}
		void SetTileState(TileState state)
		{
			m_state = state;
		}
		TileState GetDefaultTileState() const
		{
			return m_defaultState;
		}
		void SetDefaultTileState(TileState state)
		{
			m_defaultState = state;
		}

		std::shared_ptr<Texture2D> GetDefaultTexture() const
		{
			return m_pTextDefault;
		}

		void SetHasEntity(bool entity)
		{
			m_hasEntity = entity;
		}
		bool GetHasEntity() const
		{
			return m_hasEntity;
		}

		GridType GetGridType() const
		{
			return m_gridType;
		}
		
	private:
		Float2 m_tileCenter{};

		GridType m_gridType = GridType::Base;
		TileState m_state = Tile;
		TileState m_defaultState = Tile;

		std::array<GridTile*, 4> m_pAdjacentTiles{nullptr,nullptr ,nullptr ,nullptr };
		
		std::shared_ptr<Texture2D> m_pTextDefault, m_pTextChanged, m_pTextIntermediate, m_pAltTextChanged;

		bool m_hasEntity = false;
		bool m_canChange = false;
	};

}
