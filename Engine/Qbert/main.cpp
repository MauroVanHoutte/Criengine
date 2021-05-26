#include <vld.h>
#include <CriEngine.h>
#include "Qbert.h"
#include "Level.h"
#include "Renderer.h"
#include <SceneManager.h>
#include <Scene.h>
#include <GameObject.h>
#include <memory>
#include <TextureComponent.h>
#include <ResourceManager.h>
#include "JumperComponent.h"
#include <InputManager.h>
#include "JumpCommand.h"

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
	auto qBert = std::make_shared<cri::GameObject>();
	auto qBertTextureComp = new TextureComponent(qBert.get());
	qBertTextureComp->SetTexture(cri::ResourceManager::GetInstance().LoadTexture("singleQbert.png"));
	qBertTextureComp->SetWidth(30.f);
	qBertTextureComp->SetHeight(30.f);
	qBertTextureComp->m_RelativeTransform.SetPosition(-5, 0, 0);
	qBert->AddComponent("Texture", qBertTextureComp);
	auto qBertJumperComp = new JumperComponent(qBert.get(), &level, 0, 0);
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

	engine.Run();
	return 0;
}	