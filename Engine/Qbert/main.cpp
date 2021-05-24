#include <CriEngine.h>
#include "Qbert.h"
#include "Level.h"
#include "Renderer.h"
#include <SceneManager.h>
#include <Scene.h>
#undef main

int main()
{
	cri::CriEngine engine{};
	engine.Initialize();
	
	int w;
	int h;
	SDL_GetWindowSize(cri::Renderer::GetInstance().GetWindow(), &w, &h);
	auto& scene = cri::SceneManager::GetInstance().CreateScene("qbert");
	Level level{ 7, 1, 60, w / 2.f, h / 4.f, scene };
	engine.Run();
	return 0;
}	