#pragma once
#include "BaseComponent.h"

namespace dae
{
	enum class TileState
	{
		Spawn, Wall, Tile, ChangedTile
	};

	class GridTile
	{
	public:
		GridTile(Float2 position, TileState type)
			: _center{ position._x, position._y }
			, _state{ type }
		{}

		Float2 GetCenter() const
		{
			return _center;
		}
		void SetCenter(Float2 center)
		{
			_center = center;
		}

		TileState GetTileState() const
		{
			return _state;
		}
		void SetTileState(TileState state)
		{
			_state = state;
		}

	private:
		Float2 _center;
		TileState _state;
	};

	class GridTileInfo : public BaseComponent
	{
	public:
		GridTileInfo(GridTile tile, Float2 center)
			: m_gridTile(tile)
			, m_tileCenter(center)
		{}
		~GridTileInfo() override = default;

		GridTileInfo(const GridTileInfo& other) = delete;
		GridTileInfo(GridTileInfo&& other) noexcept = delete;
		GridTileInfo& operator=(const GridTileInfo& other) = delete;
		GridTileInfo& operator=(GridTileInfo&& other) noexcept = delete;

		GridTile GetTile() const 
		{
			return m_gridTile;
		}
		void SetGridTile(GridTile tile)
		{
			m_gridTile = tile;
		}
		
	private:
		GridTile m_gridTile;
		Float2 m_tileCenter{};
	};

}
