#include "MiniginPCH.h"
#include "DieObserver.h"

void dae::DieObserver::Notify(std::shared_ptr<GameObject> gO, Event event)
{
	UNREFERENCED_PARAMETER(gO);

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
