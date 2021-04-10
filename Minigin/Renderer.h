#pragma once
#include "Singleton.h"
#include "Structs.h"

struct SDL_Window;
struct SDL_Renderer;

namespace dae
{
	class Texture2D;
	
	class Renderer final : public Singleton<Renderer>
	{
	public:
		Renderer() = default;
		~Renderer() = default;

		Renderer(const Renderer& other) = delete;
		Renderer(Renderer&& other) noexcept = delete;
		Renderer& operator=(const Renderer& other) = delete;
		Renderer& operator=(Renderer&& other) noexcept = delete;
		
		void Initialize(SDL_Window* window);
		void Render() const;
		void Destroy();

		void RenderTexture(const Texture2D& texture, float x, float y) const;
		void RenderTexture(const Texture2D& texture, float x, float y, float width, float height) const;
		void RenderTexture(const Texture2D& tex, const Float4& destRect, const Float4& srcRect) const;

		int GetOpenGlDriverIndex();
		
		float GetScale() const;
		void SetScale(float scale);

		SDL_Renderer* GetSDLRenderer() const { return m_Renderer; }
		
	private:
		SDL_Renderer* m_Renderer = nullptr;
		SDL_Window* m_Window = nullptr;
		
		float m_Scale{};
		bool m_ShowDemo = true;
	};
}

