#include <vld.h>
#include <CriEngine.h>
#include "Qbert.h"



#undef main

int main()
{
	cri::CriEngine engine{};
	engine.Initialize();
	
	QbertGame::Init();

	engine.Run();
	QbertGame::Cleanup();
	return 0;
}	