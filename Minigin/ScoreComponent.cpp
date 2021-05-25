#include "MiniginPCH.h"
#include "ScoreComponent.h"

#include "GameObject.h"
#include "ScoreObserver.h"
#include "Subject.h"
#include "TextComponent.h"

dae::ScoreComponent::ScoreComponent(ScoreObserver* scoreObs)
	:m_pScoreObs(scoreObs)
{
}

dae::ScoreComponent::~ScoreComponent()
{
	m_pScoreObs = nullptr;
	m_pTextComp = nullptr;
}

void dae::ScoreComponent::Initialize()
{
	m_pTextComp = GetGameObject()->GetComponent<TextComponent>();
	// base text
	std::stringstream ssText;
	ssText << "Score: " << m_pScoreObs->GetScore();
	m_pTextComp->SetText(ssText.str());
}

void dae::ScoreComponent::Update()
{
	
	if (m_pScoreObs != nullptr && m_pTextComp != nullptr)
	{
		const int score = m_pScoreObs->GetScore();

		// dirty flag
		if (m_Score != score)
		{
			std::stringstream ssText{};
			ssText << "Score: " << score;
			m_pTextComp->SetText(ssText.str());

			// set value
			m_Score = score;
		}
	}
}

void dae::ScoreComponent::Render()
{
	
}

