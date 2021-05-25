#pragma once
#include <BaseComponent.h>
#include <Structs.h>

#include "Subject.h"

namespace dae
{
	class GridTile;
	class SpriteComponent;
	
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
		
	private:
		
		std::vector<GridTile*> m_pGridTiles;
		Float2 m_gridPosition{};
		SpriteComponent* m_pSprite1 = nullptr;
		SpriteComponent* m_pSprite2 = nullptr;

		int m_width, m_disk1{21}, m_disk2{27}, m_diskOffset{15};
		
		Subject* m_pSubject = nullptr;
	};

}