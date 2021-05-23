#include "MiniginPCH.h"
#include "FPSCounter.h"
#include "ServiceLocator.h"
#include "GameTime.h"

void dae::FPSCounter::Initialize()
{}

void dae::FPSCounter::Update()
{
	if (m_active)
	{
		// counter
		m_timer += ServiceLocator::GetGameTime()->GetInstance().GetDeltaTime();
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
