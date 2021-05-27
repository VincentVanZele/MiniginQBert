#include "MiniginPCH.h"
#include "LivesComponent.h"


#include "DieObserver.h"
#include "TextComponent.h"
#include "PlayerComponent.h"
#include "ServiceLocator.h"
#include "GameTime.h"
#include "GameObject.h"
#include "../Game/Player.h"

dae::LivesComponent::LivesComponent(DieObserver* comp)
	:m_pDieObserver(comp)
{
}

void dae::LivesComponent::Initialize()
{
	m_pTextComponent = GetGameObject()->GetComponent<TextComponent>();

	// base text
	std::stringstream ssText;
	ssText << "Lives: " << m_pDieObserver->GetLives();
	m_pTextComponent->SetText(ssText.str());
}

dae::LivesComponent::~LivesComponent()
{
	m_pDieObserver = nullptr;
	m_pTextComponent = nullptr;
}


void dae::LivesComponent::Update()
{
	if (m_pTextComponent != nullptr && m_pDieObserver != nullptr)
	{
		const int lives = m_pDieObserver->GetLives();
		
		if(m_lives != lives)
		{
			// text
			std::stringstream ssText;
			ssText << "Lives: " << lives;
			m_pTextComponent->SetText(ssText.str());

			m_lives = lives;
		}
	}
}

void dae::LivesComponent::Render()
{
}
