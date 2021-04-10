#include "MiniginPCH.h"
#include "ScoreObserver.h"

void dae::ScoreObserver::Notify(GameObject* gO, Event event)
{
	UNREFERENCED_PARAMETER(gO);

	if (event == Event::Killed)
	{
		m_KillCounter++;
		if (m_KillCounter == 10)
		{
			std::cout << "Congrats you killed 10 enemies...\n";
			m_KillAchievementTriggered = true;
			// achievement code ...
		}
		
		m_Score += 100;
	}
	else if (event == Event::TileChanged)
	{
		m_TileCounter++;
		if (m_TileCounter == 10)
		{
			std::cout << "Congrats you changed 10 tiles...\n";
			m_TileAchievementTriggered = true;
			// achievement code ...
		}

		m_Score += 50;
	}
}