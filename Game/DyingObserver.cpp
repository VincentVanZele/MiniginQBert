#include "M"
#include "DyingObserver.h"


void dae::DyingObserver::Notify(GameObject* gameObject, Event event)
{
	UNREFERENCED_PARAMETER(gameObject);

	if (event == Event::Died)
	{
		m_DiedCounter++;
		if (m_DiedCounter == 5 && m_AchievementTriggered == false)
		{
			std::cout << "Congrats you died 5 times...\n";
			m_AchievementTriggered = true;
			// achievement code ...
		}
	}
}
