#pragma once
struct SDL_Window;

namespace dae
{
	class Minigin
	{
		SDL_Window* window{};
	public:
		virtual void Initialize() = 0;
		
		void Window();
		void Cleanup();
		void Run();
	private:
	};
}