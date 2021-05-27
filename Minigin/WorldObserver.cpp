#include "MiniginPCH.h"
#include "WorldObserver.h"

#include "MiniginPCH.h"
#include "DieObserver.h"

void dae::WorldObserver::Notify(Event event)
{
	if (event == Event::TileChanged)
	{
		m_tiles++;
	}
}
