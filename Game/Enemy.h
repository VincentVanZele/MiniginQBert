#pragma once
#include <Structs.h>

#include "BaseComponent.h"
#include  "Enums.h"

namespace dae
{
	class SpriteComponent;
	enum class TileConnections;
	class Subject;
	class Observer;
	class GridTile;

	class Enemy : public BaseComponent
	{
	public:
		// Enemy 
		Enemy(GridTile* spawn);
		~Enemy() override;

		Enemy(Enemy const& other) = delete;
		Enemy(Enemy&& other) = delete;
		Enemy& operator=(Enemy const& rhs) = delete;
		Enemy& operator=(Enemy&& rhs) = delete;

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
		void TeleportToTile(GridTile* tile);

		// Textures
		void UpdateTextures(TileConnections state);

		// Subject
		void AddObserver(Observer* observer) const;
		void RemoveObserver(Observer* observer) const;

		// Lives
		void Die();

		void SetHasDied(bool died)
		{
			m_hasDied = died;
		}
		bool GetHasDied() const
		{
			return m_hasDied;
		}

		void SetLives(int lives)
		{
			m_lives = lives;
		}
		void AddLife()
		{
			m_lives += 1;
		}
		int GetLives() const
		{
			return m_lives;
		}

		void ToggleMoveRestriction()
		{
			if (m_moveRestriction)
				m_moveRestriction = false;
			else
				m_moveRestriction = true;
		}
		bool GetMoveRestriction() const
		{
			return m_moveRestriction;
		}

		Subject* GetSubject() const
		{
			return m_pSubject;
		}

		bool m_hasDied = false;

	private:
		Subject* m_pSubject = nullptr;
		std::shared_ptr<GameObject> m_gameObject;

		// Graphics
		SpriteComponent* m_pSprite = nullptr;

		// Movement
		GridTile* m_pCurrentTile;
		GridTile* m_pSpawnTile;

		bool m_moveRestriction{ false };
		bool m_needMoveUpdate{ false };
		bool m_needDirection{ true };

		const float m_WalkSpeed = 20.0f;
		Float2 m_CurrentPosition, m_TargetPosition;
		bool m_IsMoving{ false };

		// Other
		int m_lives = 10;
	};
}
