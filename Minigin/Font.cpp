#include "MiniginPCH.h"
#include "Font.h"
#include <SDL_ttf.h>

dae::Font::Font(const std::string& path, unsigned size)
: m_font(nullptr)
, m_path( path )
, m_size(size)
{
	m_font = TTF_OpenFont(path.c_str(), size);
	if (m_font == nullptr)
	{
		throw std::runtime_error(std::string("Failed to load font: ") + SDL_GetError());
	}
}

dae::Font::~Font()
{ 
	TTF_CloseFont(m_font);
}

TTF_Font* dae::Font::GetFont() const
{
	return m_font;
}

void dae::Font::SetSize(unsigned int size)
{
	m_font = TTF_OpenFont(m_path.c_str(), size);
	if (m_font == nullptr)
	{
		throw std::runtime_error(std::string("Failed to resize: ") + SDL_GetError());
	}
}