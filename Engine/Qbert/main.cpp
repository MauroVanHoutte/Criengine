#include <vld.h>
#include <CriEngine.h>
#include "Qbert.h"



#undef main

int main()
{
	cri::CriEngine engine{};
	engine.Initialize();
	
	QbertGame game{};
	game.CreateLevelScene();
	game.CreateMenuScene();

	engine.Run();

	game.Cleanup();
	return 0;
}	