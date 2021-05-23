#pragma once
#include <BaseComponent.h>
#include "SpriteComponent.h"
#include "Subject.h"

namespace dae
{
	class GridTile;
	
	// Replacement of WorldComponent
	class WorldGrid : public BaseComponent
	{
	public:
		WorldGrid(int width, Float2 pos, std::shared_ptr<GameObject> go);
		~WorldGrid() override;

		void Initialize() override;
		void Update() override;
		void Render() override;

		WorldGrid(const WorldGrid& other) = delete;
		WorldGrid(WorldGrid&& other) noexcept = delete;
		WorldGrid& operator=(const WorldGrid& other) = delete;
		WorldGrid& operator=(WorldGrid&& other) noexcept = delete;

		int GetCubeIndex(GridTile* tile) const;
		GridTile* GetCubeAtIndex(int index) const;

		void AddObserver(Observer* observer) const;
		void RemoveObserver(Observer* observer) const;

		bool m_hasKilled = false;
		bool m_hasChangedTile = false;
		
	private:
		std::vector<GridTile*> m_pGridTiles;
		Float2 m_gridPosition{};
		int m_width;
		
		Subject* m_pSubject = nullptr;
	};

}