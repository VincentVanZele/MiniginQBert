#include "MiniginPCH.h"
#include "LivesComponent.h"

#include "TextComponent.h"
#include "PlayerComponent.h"
#include "ServiceLocator.h"
#include "GameTime.h"
#include "GameObject.h"

dae::LivesComponent::LivesComponent(PlayerComponent* comp)
	:m_pPlayerComponent(comp)
{
}

void dae::LivesComponent::Initialize()
{
	m_pTextComponent = m_pGameObject.lock()->GetComponent<TextComponent>();

	// base text
	std::stringstream ssText;
	ssText << "Lives: " << m_pPlayerComponent->GetLives();
	m_pTextComponent->SetText(ssText.str());
}

void dae::LivesComponent::Update()
{
	
	if (m_pTextComponent != nullptr && m_pPlayerComponent != nullptr)
	{
		// refresh rate
		m_elapsedTime += ServiceLocator::GetGameTime()->GetInstance().GetDeltaTime();
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
