#include "MiniginPCH.h"
#include "DieObserver.h"

void dae::DieObserver::Notify(Event event)
{
	if (event == Event::Died)
	{
		m_lives--;
	}
}
