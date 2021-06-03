#include "MiniginPCH.h"
#include "DieObserver.h"

void dae::DieObserver::Notify(GameEvent event)
{
	if (event == GameEvent::Died)
	{
		m_lives--;
	}
}
