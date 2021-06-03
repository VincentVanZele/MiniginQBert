#pragma once
#include "Enums.h"

namespace dae
{	
	class GameObject;

	class Observer
	{
	public:
		virtual ~Observer() = default;
		virtual void Notify(GameEvent event) = 0;
	};
}