#pragma once
#include "Observer.h"

namespace dae
{
	class ScoreObserver : public Observer
	{
	public:
		void Notify(GameEvent event) override;
		int GetScore() const
		{
			return m_Score;
		}

	private:
		int m_Score{};
	};
}