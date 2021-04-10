#pragma once
struct SDL_Texture;

namespace dae
{
	class Texture2D
	{
	public:
		Texture2D(SDL_Texture* texture);
		~Texture2D();

		Texture2D(const Texture2D&) = delete;
		Texture2D(Texture2D&&) = delete;
		Texture2D& operator= (const Texture2D&) = delete;
		Texture2D& operator= (const Texture2D&&) = delete;

		int GetTextWidth() const;
		int GetTextHeight() const;

		SDL_Texture* GetSDLTexture() const;

		void SetInitialized(bool init);
		bool GetInitialized() const;

	private:
		SDL_Texture* m_texture;
		uint32_t m_format;
		
		int m_width = 0, m_height = 0, m_access = 0;
		
		bool m_isInitialized = false;
	};
}
