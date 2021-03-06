#include "MiniginPCH.h"
#pragma comment(lib,"xinput.lib")

// ReSharper disable once CppUnusedIncludeDirective
#include <vld.h>
#include "SDL.h"
#include "Minigin.h"

#pragma warning( push )  
#pragma warning( disable : 4100 ) // 'argv' + 'argc': unreferenced formal parameter
int main(int argc, char* argv[]) {
#pragma warning( pop )

	dae::Minigin engine;
	engine.Run();
    return 0;
}

