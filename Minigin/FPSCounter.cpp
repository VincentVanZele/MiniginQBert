#include "MiniginPCH.h"
#include "FPSCounter.h"

void dae::FPSCounter::Initialize()
{}

void dae::FPSCounter::Update(float deltaTime)
{
	if (m_active)
	{
		// counter
		m_timer += deltaTime;
		++m_counter;
		if (m_timer >= 1.0f)
		{
			// assign value
			m_FPS = m_counter;

			// reset
			m_counter = 0;
			m_timer = 0.0f;
		}
	}
}

void dae::FPSCounter::Render()
{}
