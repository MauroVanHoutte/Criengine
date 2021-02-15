#include "MiniginPCH.h"
#include "Minigin.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <SDL.h>
#include "TextObject.h"
#include "GameObject.h"
#include "Scene.h"
#include "Timer.h"
#include "TextRenderer.h"
#include "FPSCounter.h"

using namespace std;
using namespace std::chrono;

void dae::Minigin::Initialize()
{
	Timer::GetInstance();

	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	m_Window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		640,
		480,
		SDL_WINDOW_OPENGL
	);
	if (m_Window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(m_Window);
}

/**
 * Code constructing the scene world starts here
 */
void dae::Minigin::LoadGame() const
{
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	std::shared_ptr<GameObject> go = std::make_shared<GameObject>();
	go->SetTexture("background.jpg");
	scene.Add(go);

	go = std::make_shared<GameObject>();
	go->SetTexture("logo.png");
	go->SetPosition(216, 180);
	scene.Add(go);

	go = std::make_shared<GameObject>();
	FPSCounterComponent* fpsCounterComponent = new FPSCounterComponent(go.get());
	go->AddComponent("FpsCounter", fpsCounterComponent);
	scene.Add(go);

	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto to = std::make_shared<TextObject>("Programming 4 Assignment", font);
	to->SetPosition(80, 20);
	//scene.Add(to);

}

void dae::Minigin::Cleanup()
{
	TextRenderer::GetInstance()->Cleanup();
	Timer::GetInstance()->Delete();
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}

void dae::Minigin::Run()
{
	Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");
	// load fonts in the textRenderer here
	TextRenderer::GetInstance()->AddFont("CamingoCode.ttf", 12, { 255, 0, 0 });

	
	LoadGame();

	{
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();

		auto lastTime = high_resolution_clock::now();
		bool doContinue = true;
		float lag = 0.0f;
		while (doContinue)
		{
			Timer::GetInstance()->Update();

			lag += Timer::GetInstance()->GetElapsed();

			doContinue = input.ProcessInput();

			chrono::high_resolution_clock::time_point preTime = chrono::high_resolution_clock::now();

			while (lag > Timer::GetInstance()->GetStepTime())
			{
				sceneManager.FixedUpdate();
				lag -= Timer::GetInstance()->GetStepTime();
			}

			sceneManager.Update();
			sceneManager.LateUpdate();

			chrono::high_resolution_clock::time_point postTime = chrono::high_resolution_clock::now();
			Timer::GetInstance()->SetUpdateTime(chrono::duration<float>(postTime - preTime).count());

			preTime = chrono::high_resolution_clock::now();
			renderer.Render();
			postTime = chrono::high_resolution_clock::now();

			Timer::GetInstance()->SetRenderTime(chrono::duration<float>(postTime - preTime).count());
			
		}
	}

	Cleanup();
}
