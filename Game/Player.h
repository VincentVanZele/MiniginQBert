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

	enum PlayerIdx
	{
		Player1, Player2
	};
	
	class Player : public BaseComponent
	{
	public:
		// Player 
		Player(GridTile* spawn, PlayerIdx idx);
		~Player() override;

		Player(Player const& other) = delete;
		Player(Player&& other) = delete;
		Player& operator=(Player const& rhs) = delete;
		Player& operator=(Player&& rhs) = delete;

		// Overrides
		void Initialize() override;
		void Update() override;
		void Render() override;

		void Player1();
		void Player2();

		// Controller
		int GetControllerId() const { return m_ControllerId; }
		Input GetInput() const { return m_Input; }

		//Keyboard
		void HandleKeyboardInput();

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
		void SetMoveRestriction(bool stop)
		{
			m_moveRestriction = stop;
		}

		Subject* GetSubject() const
		{
			return m_pSubject;
		}

		int GetScore() 
		{
			return m_score;
		}

		bool m_hasDied = false;
		
	private:
		ActorState* m_pActivState = nullptr;

		int m_ControllerId{};
		Input m_Input{};
		Subject* m_pSubject = nullptr;
		std::shared_ptr<GameObject> m_gameObject;

		// Graphics
		SpriteComponent* m_pSprite = nullptr;
		std::shared_ptr<Texture2D> m_pTexture;

		// Movement
		GridTile* m_pCurrentTile;
		GridTile* m_pSpawnTile;

		bool m_moveRestriction{ false };
		bool m_needMoveUpdate{ false };

		const float m_WalkSpeed = 80.0f;
		Float2 m_CurrentPosition, m_TargetPosition;
		bool m_IsMoving{ false };

		// Other
		int m_lives = 10;
		int m_score = 0;
		PlayerIdx m_player{ PlayerIdx::Player1 };
	};
}
