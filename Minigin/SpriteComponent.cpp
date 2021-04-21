#include "MiniginPCH.h"
#include "SpriteComponent.h"

#include "Animation.h"
#include "Renderer.h"
#include "GameTime.h"
#include "Texture2D.h"

#include "GameObject.h"

dae::SpriteComponent::SpriteComponent()
	:BaseComponent()
	, m_deltaTime{ 0.0f }
{
}

void dae::SpriteComponent::Update(float)
{
	m_deltaTime += GameTime::GetInstance().GetDeltaTime();

	m_ActiveSprite->Update(m_deltaTime);
}

void dae::SpriteComponent::Render()
{
	m_ActiveSprite->Draw();
}

void dae::SpriteComponent::AddAnimation(std::shared_ptr<Animation> sprite)
{
	m_vSprites.push_back(sprite);
}

void dae::SpriteComponent::RemoveAnimation(const std::string& name)
{
	for (auto sprite : m_vSprites)
	{
		if (sprite->CheckName(name))
		{
			m_vSprites.erase(
				std::remove(m_vSprites.begin(), m_vSprites.end()
					, sprite)
				, m_vSprites.end()
			);
			return;
		}
	}
}

void dae::SpriteComponent::RemoveAllAnimations()
{
	for (auto sprite : m_vSprites)
	{
		m_vSprites.erase(
			std::remove(m_vSprites.begin(), m_vSprites.end()
				, sprite)
			, m_vSprites.end()
		);
	}
}

void dae::SpriteComponent::SetActiveAnimation(const std::string& name)
{
	if (m_ActiveSprite)
	{
		if (m_ActiveSprite->CheckName(name))
		{
			return;
		}
	}

	for (auto sprite : m_vSprites)
	{
		if (sprite->CheckName(name))
		{
			m_ActiveSprite = sprite;
			return;
		}
	}
}

dae::Animation& dae::SpriteComponent::GetActiveAnimation() const
{
	return *m_ActiveSprite;
}

bool dae::SpriteComponent::CheckActiveAnimation(const std::string& name)
{
	return m_ActiveSprite->CheckName(name);
}

void dae::SpriteComponent::SetAnimDeltatime(float deltaT)
{
	m_deltaTime = deltaT;
}

float dae::SpriteComponent::GetAnimDeltatime() const
{
	return m_deltaTime;
}

void dae::SpriteComponent::SetFrame(int frame)
{
	m_ActiveSprite->SetFrame(frame);
	m_deltaTime = 0.0f;
}
