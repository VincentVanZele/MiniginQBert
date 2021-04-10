#pragma once
#include "Observer.h"

namespace dae
{	
	class DyingObserver : public Observer
	{
	public:
		void Notify(GameObject* gameObject, Event event) override;
		int GetNumberDied() const
		{
			return m_DiedCounter;
		}

	private:
		int m_DiedCounter{};
		bool m_AchievementTriggered = false;
		
	};
}
