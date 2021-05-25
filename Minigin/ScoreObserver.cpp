#include "MiniginPCH.h"
#include "ScoreObserver.h"

void dae::ScoreObserver::Notify(Event event)
{
	if (event == Event::Killed)
	{
		m_Score += 100;
	}
	else if (event == Event::TileChanged)
	{
		m_Score += 50;
	}
}