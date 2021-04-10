#include "pch.h"
#pragma comment(lib,"xinput.lib")

// ReSharper disable once CppUnusedIncludeDirective
#include <iostream>
#include "Minigin.h"
#include "Game.h"

#pragma warning( push )  
#pragma warning( disable : 4100 ) // 'argv' + 'argc': unreferenced formal parameter
int main(int argc, char* argv[]) {
#pragma warning( pop )

	dae::Game game;
	game.Run();
	return 0;
}