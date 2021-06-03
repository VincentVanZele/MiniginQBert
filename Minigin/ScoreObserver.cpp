#include "MiniginPCH.h"
#include "ScoreObserver.h"

void dae::ScoreObserver::Notify(GameEvent event)
{
	if (event == GameEvent::Killed)
	{
		m_Score += 100;
	}
	else if (event == GameEvent::TileChanged)
	{
		m_Score += 50;
	}
}