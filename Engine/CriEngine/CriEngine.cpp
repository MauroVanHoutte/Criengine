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
	ServiceLocator::RegisterSoundSystem(new SDLSoundSystem());
	ServiceLocator::GetSoundSystem()->Play( "../Data/highlands.wav", 1, 100);

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

	m_QbertGame.Init();
}

/**
 * Code constructing the scene world starts here
 */
void cri::CriEngine::LoadGame() const
{
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");
	auto& input = InputManager::GetInstance();

	auto go = std::make_shared<GameObject>();
	FPSCounterComponent* fpsCounterComponent = new FPSCounterComponent(go.get());
	auto renderCommand = new SwapDoRenderTextCommand();
	renderCommand->Bind(fpsCounterComponent);
	input.AddKeyboardCommand(ButtonState::OnPressed, SDL_SCANCODE_A, renderCommand);
	input.AddControllerCommand(0, ButtonState::OnPressed, ControllerButton::ButtonA, renderCommand);
	go->AddComponent("FpsCounter", fpsCounterComponent);
	scene.Add(go);
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
				m_QbertGame.FixedUpdate();
				lag -= Timer::GetInstance()->GetStepTime();
			}

			sceneManager.Update();
			m_QbertGame.Update();
			sceneManager.LateUpdate();
			m_QbertGame.LateUpdate();


			auto postTime = std::chrono::high_resolution_clock::now();
			Timer::GetInstance()->SetUpdateTime(std::chrono::duration<float>(postTime - preTime).count());

			SDL_RenderClear(renderer.GetSDLRenderer());
			preTime = std::chrono::high_resolution_clock::now();
			renderer.Render();
			m_QbertGame.Render();
			postTime = std::chrono::high_resolution_clock::now();
			Timer::GetInstance()->SetRenderTime(std::chrono::duration<float>(postTime - preTime).count());
			SDL_RenderPresent(renderer.GetSDLRenderer());

		}
	}

	Cleanup();
}
