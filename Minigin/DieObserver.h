#pragma once
#include "Observer.h"

namespace dae
{
	class DieObserver : public Observer
	{
	public:
		void Notify(GameEvent event) override;
		int GetLives() const
		{
			return m_lives;
		}

	private:
		int m_lives{10};
	};
}