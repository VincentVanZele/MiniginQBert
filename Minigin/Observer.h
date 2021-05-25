#pragma once
#include "Enums.h"

namespace dae
{	
	class GameObject;

	class Observer
	{
	public:
		virtual ~Observer() = default;
		virtual void Notify(Event event) = 0;
	};
}