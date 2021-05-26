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

Level* QbertGame::m_pLevel = nullptr;

void QbertGame::Init()
{
	int w;
	int h;
	SDL_GetWindowSize(cri::Renderer::GetInstance().GetWindow(), &w, &h);
	auto& scene = cri::SceneManager::GetInstance().CreateScene("qbert");
	m_pLevel = new Level{ 7, 1, 60, w / 2.f, h / 4.f, scene };
	auto qBert = std::make_shared<cri::GameObject>();
	auto qBertTextureComp = new SingleRowAnimationComponent(qBert.get(), 4, 2, cri::ResourceManager::GetInstance().LoadTexture("QbertSpriteSheet.png"));
	qBertTextureComp->SetWidth(30.f);
	qBertTextureComp->SetHeight(30.f);
	qBertTextureComp->SetAnimation(2);
	
	qBert->AddComponent("Texture", qBertTextureComp);
	auto qBertJumperComp = new JumperComponent(qBert.get(), m_pLevel, 0, 0);
	qBert->AddComponent("Jumper", qBertJumperComp);
	scene.Add(qBert);

	auto jumpUpLeftCommand = new JumpCommand(-1, -1);
	jumpUpLeftCommand->Bind(qBertJumperComp);

	cri::InputManager::GetInstance().AddKeyboardCommand(cri::ButtonState::OnPressed, SDL_Scancode::SDL_SCANCODE_KP_7, jumpUpLeftCommand);

	auto jumpUpRightCommand = new JumpCommand(1, -1);
	jumpUpRightCommand->Bind(qBertJumperComp);

	cri::InputManager::GetInstance().AddKeyboardCommand(cri::ButtonState::OnPressed, SDL_Scancode::SDL_SCANCODE_KP_9, jumpUpRightCommand);

	auto jumpDownLeftCommand = new JumpCommand(-1, 1);
	jumpDownLeftCommand->Bind(qBertJumperComp);

	cri::InputManager::GetInstance().AddKeyboardCommand(cri::ButtonState::OnPressed, SDL_Scancode::SDL_SCANCODE_KP_1, jumpDownLeftCommand);

	auto jumpDownRightCommand = new JumpCommand(1, 1);
	jumpDownRightCommand->Bind(qBertJumperComp);

	cri::InputManager::GetInstance().AddKeyboardCommand(cri::ButtonState::OnPressed, SDL_Scancode::SDL_SCANCODE_KP_3, jumpDownRightCommand);

	auto go = std::make_shared<cri::GameObject>();
	FPSCounterComponent* fpsCounterComponent = new FPSCounterComponent(go.get());
	auto renderCommand = new SwapDoRenderTextCommand();
	renderCommand->Bind(fpsCounterComponent);
	cri::InputManager::GetInstance().AddKeyboardCommand(cri::ButtonState::OnPressed, SDL_SCANCODE_A, renderCommand);
	cri::InputManager::GetInstance().AddControllerCommand(0, cri::ButtonState::OnPressed, cri::ControllerButton::ButtonA, renderCommand);
	go->AddComponent("FpsCounter", fpsCounterComponent);
	scene.Add(go);
}

void QbertGame::Cleanup()
{
	if (m_pLevel)
	{
		delete m_pLevel;
	}
}
