#include "MiniginPCH.h"
#include <SDL.h>
#include <SDL_ttf.h>

#include "TextObject.h"
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"

dae::TextObject::TextObject(const std::string& text, const std::shared_ptr<Font>& font)
	: m_dirtyFlag(true)
	, m_text(text)
	, m_font(font)
	, m_texture(nullptr)
{
	
}

void dae::TextObject::Initialize()
{
}

void dae::TextObject::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	if (m_dirtyFlag)
	{
		const SDL_Color color = { 255,255,255 }; // only white text is supported now
		const auto surf = TTF_RenderText_Blended(m_font->GetFont(), m_text.c_str(), color);
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

void dae::TextObject::Render() const
{
	if (m_texture != nullptr)
	{
		const auto pos = m_transform.GetPosition();
		Renderer::GetInstance().RenderTexture(*m_texture, pos._x, pos._y);
	}
}

void dae::TextObject::SetText(const std::string& text)
{
	m_text = text;
	m_dirtyFlag = true;
}

void dae::TextObject::SetPosition(const float x, const float y)
{
	m_transform.SetPosition(x, y, 0.0f);
}


