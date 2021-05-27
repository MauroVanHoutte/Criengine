#include "CriEngine.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <SDL.h>
#include "GameObject.h"
#include "Scene.h"
#include "Timer.h"
#include "TextRenderer.h"
#include "FPSCounter.h"
#include "SwapDoRenderTextCommand.h"
#include "ServiceLocator.h"
#include "SDLSoundSystem.h"
#include "LoggingSystem.h"

void cri::CriEngine::Initialize()
{
	Timer::GetInstance();
	ResourceManager::GetInstance().Init("../Data/");
	ServiceLocator::RegisterSoundSystem(new SDLSoundSystem());
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
void cri::CriEngine::LoadGame() const
{

}

void cri::CriEngine::Cleanup()
{
	TextRenderer::GetInstance()->Cleanup();
	Timer::GetInstance()->Delete();
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	ServiceLocator::Destroy();
	SDL_Quit();
}

void cri::CriEngine::Run()
{
	// tell the resource manager where he can find the game data
	// load fonts in the textRenderer here
	TextRenderer::GetInstance()->AddFont("CamingoCode.ttf", 12, { 255, 0, 0 });
	
	
	LoadGame();

	{
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();

		auto lastTime = std::chrono::high_resolution_clock::now();
		bool doContinue = true;
		float lag = 0.0f;
		while (doContinue)
		{
			Timer::GetInstance()->Update();

			lag += Timer::GetInstance()->GetElapsed();

			SDL_Event event;
			while(SDL_PollEvent(&event))
			{
				if (event.type == SDL_QUIT)
				{
					doContinue = false;
				}
			}

			input.ProcessInput();

			auto preTime = std::chrono::high_resolution_clock::now();

			while (lag > Timer::GetInstance()->GetStepTime())
			{
				sceneManager.FixedUpdate();
				lag -= Timer::GetInstance()->GetStepTime();
			}

			sceneManager.Update();
			sceneManager.LateUpdate();


			auto postTime = std::chrono::high_resolution_clock::now();
			Timer::GetInstance()->SetUpdateTime(std::chrono::duration<float>(postTime - preTime).count());

			SDL_RenderClear(renderer.GetSDLRenderer());
			preTime = std::chrono::high_resolution_clock::now();
			renderer.Render();
			postTime = std::chrono::high_resolution_clock::now();
			Timer::GetInstance()->SetRenderTime(std::chrono::duration<float>(postTime - preTime).count());
			SDL_RenderPresent(renderer.GetSDLRenderer());

		}
	}

	Cleanup();
}
