#pragma once
#include "Minigin.h"

namespace dae
{
	class Player;
	class WorldGrid;

	class Game
	{
	public:
		void Run();
		void LoadScenes();
		void LoadAllScenes();
		
		static void SwitchTitle();

		static void SwitchLevel1();
		static void SwitchLevel2();
		static void SwitchLevel3();

		static void SwitchVersus();
		
		static void SwitchEndScreen();

		static void Reset();
	};
}