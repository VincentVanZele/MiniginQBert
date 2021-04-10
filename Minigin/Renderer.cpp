#include "MiniginPCH.h"
#include <SDL.h>
#include "imgui.h"
#include "backends/imgui_impl_opengl2.h"
#include "backends/imgui_impl_sdl.h"

#include "Renderer.h"
#include "SceneManager.h"
#include "Texture2D.h"


void dae::Renderer::Initialize(SDL_Window * window)
{
	m_Window = window;
	m_Renderer = SDL_CreateRenderer(window, GetOpenGlDriverIndex(), SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	
	if (m_Renderer == nullptr)
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(window, SDL_GL_GetCurrentContext());
	ImGui_ImplOpenGL2_Init();
}

void dae::Renderer::Render() const 
{
	SDL_RenderClear(m_Renderer);
	
	SceneManager::GetInstance().Render();

	// ImGui
	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplSDL2_NewFrame(m_Window);
	ImGui::NewFrame();

	if (m_ShowDemo)
	{
		ImGui::ShowDemoWindow();
	}

	ImGui::Render();
	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
	
	SDL_RenderPresent(m_Renderer);
}

void dae::Renderer::Destroy()
{
	ImGui_ImplOpenGL2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
	
	if (m_Renderer != nullptr)
	{
		SDL_DestroyRenderer(m_Renderer);
		m_Renderer = nullptr;
	}
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y) const
{
	SDL_Rect dst;
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, const float width, const float height) const
{
	SDL_Rect dst;
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = static_cast<int>(width);
	dst.h = static_cast<int>(height);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void dae::Renderer::RenderTexture(const Texture2D& tex, const Float4& destRect, const Float4& srcRect) const
{
	SDL_Rect dst{
		static_cast<int>((destRect._x * m_Scale)),
		static_cast<int>((destRect._y * m_Scale)),
		static_cast<int>((destRect._z * m_Scale)),
		static_cast<int>((destRect._w * m_Scale)) };

	SDL_Rect src{
		static_cast<int>((srcRect._x)),
		static_cast<int>((srcRect._y)),
		static_cast<int>((srcRect._z)),
		static_cast<int>((srcRect._w)) };

	SDL_RenderCopy(GetSDLRenderer(), tex.GetSDLTexture(), &src, &dst);
}

float dae::Renderer::GetScale() const
{
	return m_Scale;
}

void dae::Renderer::SetScale(float scale)
{
	m_Scale = scale;
}

int dae::Renderer::GetOpenGlDriverIndex()
{
	auto openglIndex = -1;
	const auto driveCount = SDL_GetNumRenderDrivers();
	for(auto i = 0; i < driveCount; i++)
	{
		SDL_RendererInfo info;
		if(!SDL_GetRenderDriverInfo(i,&info))
		{
			if (!strcmp(info.name, "opengl"))
			{
				openglIndex = i;
			}
		}
	}
	return openglIndex;
}