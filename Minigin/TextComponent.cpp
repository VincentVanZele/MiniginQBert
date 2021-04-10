#include "MiniginPCH.h"
#include "TextComponent.h"
#include <SDL_ttf.h>
#include "Renderer.h"
#include "GameObject.h"

dae::TextComponent::TextComponent(const std::shared_ptr<Font>& font, const std::string& text, const Float3 color)
	: m_font{ font }
	, m_text{ text }
	, m_Color{ color }
	, m_dirtyFlag{ true }
	, m_texture{ nullptr }
{
	
}

void dae::TextComponent::Initialize()
{
}

void dae::TextComponent::SetColor(Float3 color)
{
	m_Color = color;
}

void dae::TextComponent::SetText(const std::string& text)
{
	m_text = text;
	m_dirtyFlag = true;
}

void dae::TextComponent::SetTextSize(unsigned int size)
{
	m_font->SetSize(size);
	m_dirtyFlag = true;
}

void dae::TextComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	if (m_dirtyFlag)
	{
		const auto surf = TTF_RenderText_Blended(m_font->GetFont(), m_text.c_str(), {static_cast<Uint8>(m_Color._x),static_cast<Uint8>(m_Color._y),static_cast<Uint8>(m_Color._z)});
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_texture = std::make_shared<Texture2D>(texture);
		m_dirtyFlag = false;
	}
}

void dae::TextComponent::Render()
{
	if (m_texture != nullptr)
	{
		const Float3 pos = m_pGameObject->GetPosition();
		Renderer::GetInstance().RenderTexture(*m_texture, pos._x, pos._y);
	}
}
