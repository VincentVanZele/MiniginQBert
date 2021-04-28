#pragma once
#include "BaseComponent.h"
#include "SpriteComponent.h"
#include "ActorState.h"

#include  "Enums.h"

// Replaces PlayerComponent.h
namespace dae
{
	class Subject;
	class Observer;
	class GridTile;
	
	class Player : public BaseComponent
	{
	public:
		Player(PlayerIndex player = PlayerIndex::PlayerOne);
		~Player() override;
		
		Player(const Player& other) = delete;
		Player(Player&& other) noexcept = delete;
		Player& operator=(const Player& other) = delete;
		Player& operator=(Player&& other) noexcept = delete;

		void Initialize() override;
		void Update(float deltaTime) override;
		void Render() override;

		int GetControllerId() const { return m_ControllerId; }
		float GetWalkSpeed() const { return m_WalkSpeed; }
		Input GetInput() const { return m_Input; }

		void SetCurrentTile(GridTile* tile)
		{
			m_pCurrentTile = tile;
		}
		GridTile* GetCurrentTile() const
		{
			return m_pCurrentTile;
		}

		void ToTile(GridTile* tile);

		void AddObserver(Observer* observer);
		void RemoveObserver(Observer* observer);

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
		
		SpriteComponent* m_pSprite = nullptr;
		Texture2D* m_pTexture;

		GridTile* m_pCurrentTile;
		const float m_WalkSpeed = 80.0f;

		Subject* m_pSubject = nullptr;
		
		int m_lives = 10;
	};
}
