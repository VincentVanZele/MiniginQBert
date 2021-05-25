#include "MiniginPCH.h"
#include "DieObserver.h"

void dae::DieObserver::Notify(Event event)
{

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
	else if(event == Event::Killed)
	{
		
	}
}
