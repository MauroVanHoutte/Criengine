#include <CriEngine.h>
#include "Qbert.h"

int main()
{
	cri::CriEngine engine{};
	engine.Initialize();
	QbertGame::Init();
	engine.Run();
	return 0;
}	