#pragma once
#include "Observer.h"

namespace dae
{
	class ScoreObserver : public Observer
	{
	public:
		void Notify(GameObject* gO, Event event) override;
		int GetScore() const
		{
			return m_Score;
		}

	private:
		int m_Score{};

		int m_KillCounter{};
		int m_TileCounter{};

		bool m_KillAchievementTriggered = false;
		bool m_TileAchievementTriggered = false;
	};
}