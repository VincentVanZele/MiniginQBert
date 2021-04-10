#include "MiniginPCH.h"
#include "LivesComponent.h"

#include "TextComponent.h"
#include "PlayerComponent.h"

dae::LivesComponent::LivesComponent(PlayerComponent* comp)
	:m_pPlayerComponent(comp)
{
}

void dae::LivesComponent::Initialize()
{
	m_pTextComponent = m_pGameObject->GetComponent<TextComponent>();

	// base text
	std::stringstream ssText;
	ssText << "Lives: " << m_pPlayerComponent->GetLives();
	m_pTextComponent->SetText(ssText.str());
}

void dae::LivesComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
	
	if (m_pTextComponent != nullptr && m_pPlayerComponent != nullptr)
	{
		// refresh rate
		m_elapsedTime += deltaTime;
		if (m_elapsedTime >= m_refreshRate)
		{
			// reset
			m_elapsedTime = 0;
			// text
			std::stringstream ssText;
			ssText << "Lives: " << m_pPlayerComponent->GetLives();
			m_pTextComponent->SetText(ssText.str());
		}
	}
}

void dae::LivesComponent::Render()
{
}
