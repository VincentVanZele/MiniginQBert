#pragma once
#include "Observer.h"

namespace dae
{
	class WorldObserver : public Observer
	{
	public:
		void Notify(Event event) override;
		int GetFlippedTiles() const
		{
			return m_tiles;
		}

	private:
		int m_tiles{};
	};
}