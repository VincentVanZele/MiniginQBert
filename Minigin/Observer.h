#pragma once
#include "Enums.h"

namespace dae
{	
	class GameObject;

	class Observer
	{
	public:
		virtual ~Observer() = default;
		virtual void Notify(dae::GameObject* gameObject, Event event) = 0;
	};
}