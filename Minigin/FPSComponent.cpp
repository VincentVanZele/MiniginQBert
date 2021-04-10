#include "MiniginPCH.h"
#include "FPSComponent.h"
#include "FPSCounter.h"
#include "TextComponent.h"

void dae::FPSComponent::Initialize()
{
	m_pFPSCounter = m_pGameObject->GetComponent<FPSCounter>();
	m_pTextComponent = m_pGameObject->GetComponent<TextComponent>();
}

void dae::FPSComponent::Update(float deltaTime)
{
	if (m_pFPSCounter != nullptr && m_pTextComponent != nullptr)
	{
		// refresh rate
		m_elapsedTime += deltaTime;
		if (m_elapsedTime >= m_refreshRate)
		{
			// reset
			m_elapsedTime = 0;

			// text (string crashes of course)
			std::stringstream ssText;
			ssText << "FPS: " << m_pFPSCounter->GetFPS();
			m_pTextComponent->SetText(ssText.str());
		}
	}
}

void dae::FPSComponent::Render()
{
}
