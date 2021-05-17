#pragma once
#include "BaseComponent.h"
#include "SpriteComponent.h"
#include "ActorState.h"

#include  "Enums.h"

// Replaces PlayerComponent.h
namespace dae
{
	enum class TileConnections;
	class Subject;
	class Observer;
	class GridTile;
	
	class Player : public BaseComponent
	{
	public:
		// Player 
		Player(PlayerIndex player = PlayerIndex::PlayerOne);
		virtual ~Player();

		Player(Player const& other) = delete;
		Player(Player&& other) = delete;
		Player& operator=(Player const& rhs) = delete;
		Player& operator=(Player&& rhs) = delete;

		// Overrides
		void Initialize() override;
		void Update(float deltaTime) override;
		void Render() override;

		// Controller
		int GetControllerId() const { return m_ControllerId; }
		Input GetInput() const { return m_Input; }

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
		void SetBaseTile(GridTile* tile);

		// Textures
		void UpdateTextures(TileConnections state);

		// Subject
		void AddObserver(Observer* observer) const;
		void RemoveObserver(Observer* observer) const;

		// Lives
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

		bool m_hasDied = false;
		
	private:
		PlayerIndex m_PlayerNumber = PlayerIndex::PlayerOne;
		ActorState* m_pActivState = nullptr;

		int m_ControllerId{};
		Input m_Input{};
		Subject* m_pSubject = nullptr;

		// Graphics
		SpriteComponent* m_pSprite = nullptr;
		std::shared_ptr<Texture2D> m_pTexture;

		// Movement
		GridTile* m_pCurrentTile;
		bool m_needMoveUpdate{ false };

		const float m_WalkSpeed = 80.0f;
		Float2 m_CurrentPosition, m_TargetPosition;
		bool m_IsMoving{ false };

		// Other
		int m_lives = 10;	
	};
}
