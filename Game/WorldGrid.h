#pragma once
#include <BaseComponent.h>
#include <Structs.h>

#include "Subject.h"

namespace dae
{
	enum class GridType;
	class GridTile;
	class SpriteComponent;
	
	// Replacement of WorldComponent
	class WorldGrid : public BaseComponent
	{
	public:
		WorldGrid(GridType type, int width, Float2 pos, std::shared_ptr<GameObject> go);
		~WorldGrid() override;

		void Initialize() override;
		void Update() override;
		void Render() override;

		WorldGrid(const WorldGrid& other) = delete;
		WorldGrid(WorldGrid&& other) noexcept = delete;
		WorldGrid& operator=(const WorldGrid& other) = delete;
		WorldGrid& operator=(WorldGrid&& other) noexcept = delete;

		int GetCubeIndex(GridTile* tile) const;
		GridTile* GetCubeAtIndex(int idx) const;
		GridTile* GetFrontCube() const;

		void AddObserver(Observer* observer) const;
		void RemoveObserver(Observer* observer) const;

		int GetNumberOfChangeableTiles() const
		{
			return (int)m_pChangeableTiles.size();
		}
		
		int GetNumberOfTiles() const
		{
			return (int)m_pGridTiles.size();
		}

		Subject* GetSubject() const
		{
			return m_pSubject;
		}

		std::vector<GridTile*> GetGridTiles() const
		{
			return m_pGridTiles;
		}
		
	private:
		std::vector<GridTile*> m_pGridTiles;
		std::vector<GridTile*> m_pChangeableTiles;
		
		Float2 m_gridPosition{}, m_tempPos{0,0};
		
		SpriteComponent* m_pSprite1 = nullptr;
		SpriteComponent* m_pSprite2 = nullptr;

		int m_size, m_disk1{21}, m_disk2{27}, m_diskOffset{15},
		    m_offset{ 1 }, m_edge{ 1 }, m_counter{ 0 };
		
		Subject* m_pSubject = nullptr;
	};

}