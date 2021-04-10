#include "MiniginPCH.h"
#include "Texture2D.h"
#include <SDL.h>

dae::Texture2D::Texture2D(SDL_Texture* texture)
	: m_texture(texture)
{
	SDL_QueryTexture(m_texture, &m_format, &m_access, &m_width, &m_height);
}

dae::Texture2D::~Texture2D()
{
	SDL_DestroyTexture(m_texture);
}

int dae::Texture2D::GetTextWidth() const
{
	return m_width;
}

int dae::Texture2D::GetTextHeight() const
{
	return m_height;
}

SDL_Texture* dae::Texture2D::GetSDLTexture() const
{
	return m_texture;
}

void dae::Texture2D::SetInitialized(bool init)
{
	m_isInitialized = init;
}

bool dae::Texture2D::GetInitialized() const
{
	return m_isInitialized;
}
