#pragma once
#include "BaseComponent.h"
#include "Subject.h"

enum class PlayerIndex;

namespace dae
{
	class Subject;
	class Observer;

	class PlayerComponent : public BaseComponent
	{
	public:
		PlayerComponent(PlayerIndex player);
		~PlayerComponent() override;
		
		PlayerComponent(const PlayerComponent& other) = delete;
		PlayerComponent(PlayerComponent&& other) noexcept = delete;
		PlayerComponent& operator=(const PlayerComponent& other) = delete;
		PlayerComponent& operator=(PlayerComponent&& other) noexcept = delete;

		void Initialize() override;
		void Update(float deltaTime) override;
		void Render() override;

		int GetControllerId() const
		{
			return m_ControllerId;
		}

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

		// variables
		// 
		// temporary -> will be changed to state machine
		bool m_hasDied = false;
	
	private:
		PlayerIndex m_PlayerNumber;
		int m_ControllerId{};

		Subject* m_pSubject = nullptr;

		
		
		int m_lives = 10;
	};

}
