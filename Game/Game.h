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
		static void SwitchScene();
	};
}