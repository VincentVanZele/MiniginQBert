#pragma once
struct SDL_Window;

namespace dae
{
	class Minigin
	{
		SDL_Window* window{};
	public:
		
		void Window();
		void LoadGame() const;
		void Cleanup();
		void Run();
	private:
	};
}