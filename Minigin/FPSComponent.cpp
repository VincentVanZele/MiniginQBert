#include "MiniginPCH.h"
#include "FPSComponent.h"
#include "FPSCounter.h"
#include "GameTime.h"
#include "ServiceLocator.h"
#include "TextComponent.h"
#include "GameObject.h"

void dae::FPSComponent::Initialize()
{
	m_pFPSCounter = m_pGameObject.lock()->GetComponent<FPSCounter>();
	m_pTextComponent = m_pGameObject.lock()->GetComponent<TextComponent>();
}

void dae::FPSComponent::Update()
{
	if (m_pFPSCounter != nullptr && m_pTextComponent != nullptr)
	{
		// refresh rate
		m_elapsedTime += ServiceLocator::GetGameTime()->GetInstance().GetDeltaTime();
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
