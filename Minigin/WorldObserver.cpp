#include "MiniginPCH.h"
#include "WorldObserver.h"

#include "MiniginPCH.h"
#include "DieObserver.h"

void dae::WorldObserver::Notify(GameEvent event)
{
	if (event == GameEvent::TileChanged)
	{
		m_tiles++;
	}
}
