#pragma once
#include <BaseComponent.h>
#include "SpriteComponent.h"
#include "Subject.h"

namespace dae
{
	// Replacement of WorldComponent
	class WorldGrid : public BaseComponent
	{
	public:
		WorldGrid(std::vector<std::weak_ptr<GameObject>> gridTiles);
		~WorldGrid() override;

		void Initialize() override;
		void Update(float deltaTime) override;
		void Render() override;

		WorldGrid(const WorldGrid& other) = delete;
		WorldGrid(WorldGrid&& other) noexcept = delete;
		WorldGrid& operator=(const WorldGrid& other) = delete;
		WorldGrid& operator=(WorldGrid&& other) noexcept = delete;

		void AddObserver(Observer* observer) const;
		void RemoveObserver(Observer* observer) const;

		bool m_hasKilled = false;
		bool m_hasChangedTile = false;
		
	private:
		std::vector<std::weak_ptr<GameObject>> m_pGridTiles{};
		
		float m_MinDistance = 15.f;
		Subject* m_pSubject = nullptr;
	};

}