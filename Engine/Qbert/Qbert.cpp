#include "Qbert.h"
#include <InputManager.h>
#include <SceneManager.h>
#include <Scene.h>
#include "HealthCounter.h"
#include "QbertHealthComponent.h"
#include "QbertScoreComponent.h"
#include "ScoreCounter.h"
#include <ServiceLocator.h>
#include <Renderer.h>
#include "Level.h"
#include "SingleRowAnimationComponent.h"
#include <ResourceManager.h>
#include "JumperComponent.h"
#include "JumpCommand.h"
#include <FPSCounter.h>
#include <SwapDoRenderTextCommand.h>
#include "QbertMainMenuComponent.h"
#include "MenuUpCommand.h"
#include "MenuDownCommand.h"
#include "MenuButtonClickCommand.h"

void QbertGame::Init()
{
	
}

void QbertGame::Cleanup()
{
	if (m_pLevel)
	{
		delete m_pLevel;
	}
}

void QbertGame::CreateMenuScene()
{
	auto& scene = cri::SceneManager::GetInstance().CreateScene("menu");
	int sceneIdx = cri::SceneManager::GetInstance().GetCurrentSceneIdx();

	int screenW;
	int screenH;
	SDL_GetWindowSize(cri::Renderer::GetInstance().GetWindow(), &screenW, &screenH);

	auto menu = std::make_shared<cri::GameObject>();
	menu->m_Transform.SetPosition(float(2.f*screenW/5.f), float(screenH/2.f), 0.f);
	auto menuComponent = new QbertMainMenuComponent(menu.get());
	menu->AddComponent("menu", menuComponent);
	menuComponent->AddObserver(this);

	auto menuUpCommand = new MenuUpCommand();
	menuUpCommand->Bind(menuComponent);
	cri::InputManager::GetInstance().AddKeyboardCommand(sceneIdx, cri::ButtonState::OnPressed, SDL_SCANCODE_KP_8, menuUpCommand);
	menuUpCommand = new MenuUpCommand();
	menuUpCommand->Bind(menuComponent);
	cri::InputManager::GetInstance().AddControllerCommand(0, sceneIdx, cri::ButtonState::OnPressed, cri::ControllerButton::DPadUp, menuUpCommand);

	auto menuDownCommand = new MenuDownCommand();
	menuDownCommand->Bind(menuComponent);
	cri::InputManager::GetInstance().AddKeyboardCommand(sceneIdx, cri::ButtonState::OnPressed, SDL_SCANCODE_KP_2, menuDownCommand);
	menuDownCommand = new MenuDownCommand();
	menuDownCommand->Bind(menuComponent);
	cri::InputManager::GetInstance().AddControllerCommand(0, sceneIdx, cri::ButtonState::OnPressed, cri::ControllerButton::DPadDown, menuDownCommand);

	auto menuClickCommand = new MenuButtonClickCommand();
	menuClickCommand->Bind(menuComponent);
	cri::InputManager::GetInstance().AddKeyboardCommand(sceneIdx, cri::ButtonState::OnPressed, SDL_SCANCODE_RETURN, menuClickCommand);
	menuClickCommand = new MenuButtonClickCommand();
	menuClickCommand->Bind(menuComponent);
	cri::InputManager::GetInstance().AddControllerCommand(0, sceneIdx, cri::ButtonState::OnPressed, cri::ControllerButton::ButtonA, menuClickCommand);

	scene.Add(menu);

}

void QbertGame::CreateLevelScene()
{
	auto& scene = cri::SceneManager::GetInstance().CreateScene("qbert");
	int sceneIdx = cri::SceneManager::GetInstance().GetCurrentSceneIdx();
	m_QBert = std::make_shared<cri::GameObject>();
	auto qBertTextureComp = new SingleRowAnimationComponent(m_QBert.get(), 4, 2, cri::ResourceManager::GetInstance().LoadTexture("QbertSpriteSheet.png"));
	qBertTextureComp->SetWidth(30.f);
	qBertTextureComp->SetHeight(30.f);
	qBertTextureComp->SetAnimation(2);

	m_QBert->AddComponent("Texture", qBertTextureComp);
	auto qBertJumperComp = new JumperComponent(m_QBert.get(), 0.7f, "jumpQbert.wav");
	m_QBert->AddComponent("Jumper", qBertJumperComp);
	scene.Add(m_QBert);

	auto jumpUpLeftCommand = new JumpCommand(-1, -1);
	jumpUpLeftCommand->Bind(qBertJumperComp);

	cri::InputManager::GetInstance().AddKeyboardCommand(sceneIdx, cri::ButtonState::Down, SDL_Scancode::SDL_SCANCODE_KP_7, jumpUpLeftCommand);

	auto jumpUpRightCommand = new JumpCommand(1, -1);
	jumpUpRightCommand->Bind(qBertJumperComp);

	cri::InputManager::GetInstance().AddKeyboardCommand(sceneIdx, cri::ButtonState::Down, SDL_Scancode::SDL_SCANCODE_KP_9, jumpUpRightCommand);

	auto jumpDownLeftCommand = new JumpCommand(-1, 1);
	jumpDownLeftCommand->Bind(qBertJumperComp);

	cri::InputManager::GetInstance().AddKeyboardCommand(sceneIdx, cri::ButtonState::Down, SDL_Scancode::SDL_SCANCODE_KP_1, jumpDownLeftCommand);

	auto jumpDownRightCommand = new JumpCommand(1, 1);
	jumpDownRightCommand->Bind(qBertJumperComp);

	cri::InputManager::GetInstance().AddKeyboardCommand(sceneIdx, cri::ButtonState::Down, SDL_Scancode::SDL_SCANCODE_KP_3, jumpDownRightCommand);

	auto go = std::make_shared<cri::GameObject>();
	FPSCounterComponent* fpsCounterComponent = new FPSCounterComponent(go.get());
	auto renderCommand = new SwapDoRenderTextCommand();
	renderCommand->Bind(fpsCounterComponent);
	cri::InputManager::GetInstance().AddKeyboardCommand(sceneIdx, cri::ButtonState::OnPressed, SDL_SCANCODE_A, renderCommand);
	renderCommand = new SwapDoRenderTextCommand();
	renderCommand->Bind(fpsCounterComponent);
	cri::InputManager::GetInstance().AddControllerCommand(sceneIdx, 0, cri::ButtonState::OnPressed, cri::ControllerButton::ButtonA, renderCommand);
	go->AddComponent("FpsCounter", fpsCounterComponent);
	scene.Add(go);
}

void QbertGame::SetupLevel()
{
	auto& scene = cri::SceneManager::GetInstance().GetCurrentScene();

	int w;
	int h;
	SDL_GetWindowSize(cri::Renderer::GetInstance().GetWindow(), &w, &h);
	m_pLevel = new Level{ 7, m_CurrentDifficulty, 60, w / 2.f, h / 4.f, scene, this };
	m_QBert->GetComponent<JumperComponent>()->SetStartPos(m_pLevel, 0, 0);
	cri::SceneManager::GetInstance().GetCurrentScene().MoveObjectToFront(m_QBert.get());

}

void QbertGame::OnNotify(Event event)
{
	switch (event)
	{
	case Event::PlayerDeath:
		break;
	case Event::ColorChange:
		break;
	case Event::CoilyDeath:
		break;
	case Event::RemainingDisc:
		break;
	case Event::SlickSamCaught:
		break;
	case Event::StartSinglePlayer:
		cri::SceneManager::GetInstance().NextScene();
		SetupLevel();
		break;
	case Event::StartCoop:
		break;
	case Event::StartVersus:
		break;
	case Event::TileJumpedOn:
		if (m_pLevel->Completed())
		{
			++m_CurrentDifficulty;
			delete m_pLevel;
			SetupLevel();
		}
		break;
	default:
		break;
	}
}
