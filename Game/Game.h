#pragma once

namespace dae
{
	class Player;
	class WorldGrid;

	class Game
	{
	public:
		void Run() const;
		void LoadScenes() const;

		static void LoadAllScenes();
		
		static void SwitchTitle();

		static void SwitchLevel1();
		static void SwitchLevel2();
		static void SwitchLevel3();

		static void SwitchVersus();
		
		static void SwitchEndScreen();
		static void SwitchEndScreen(int player);

		static void Reset();
	};
}