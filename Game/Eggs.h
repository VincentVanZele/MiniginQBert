#pragma once
#include <Structs.h>
#include "BaseComponent.h"

namespace dae
{
	class SpriteComponent;
	enum class TileConnections;
	class Subject;
	class Observer;
	class GridTile;

	enum class EggType
	{
		Green, Purple, Red
	};

	class Eggs : public BaseComponent
	{
	public:
		// Egg 
		Eggs(GridTile* base, EggType type, Float2 spawn, bool delayed);
		~Eggs() override;

		Eggs(Eggs const& other) = delete;
		Eggs(Eggs&& other) = delete;
		Eggs& operator=(Eggs const& rhs) = delete;
		Eggs& operator=(Eggs&& rhs) = delete;

		// Overrides
		void Initialize() override;
		void Update() override;
		void Render() override;

		// Tile
		void SetCurrentTile(GridTile* tile)
		{
			m_pCurrentTile = tile;
		}
		GridTile* GetCurrentTile() const
		{
			return m_pCurrentTile;
		}

		void MoveTo(TileConnections connection);
		void MoveToTile(GridTile* tile);

	private:
		// Graphics
		SpriteComponent* m_pSprite = nullptr;

		// Movement
		GridTile* m_pCurrentTile{nullptr};
		GridTile* m_pBaseTile{nullptr};

		bool m_needMoveUpdate{ false };
		bool m_goLeft{ false };

		const float m_WalkSpeed = 40.0f;
		Float2 m_CurrentPosition, m_TargetPosition, m_SpawnPos;
		bool m_IsMoving{ false };

		// Type
		EggType m_eggType;

		// Game
		bool m_isDelayed{ false };
		float m_elapsedTime;
		int m_delay{ 4 };
	};
}
