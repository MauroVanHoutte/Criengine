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
#include "QbertJumperComponent.h"
#include "CoilyJumperComponent.h"
#include "JumpCommand.h"
#include <FPSCounter.h>
#include <SwapDoRenderTextCommand.h>
#include "QbertMainMenuComponent.h"
#include "MenuUpCommand.h"
#include "MenuDownCommand.h"
#include "MenuButtonClickCommand.h"
#include "TestCommand.h"
#include <rapidjson.h>
#include <document.h>
#include <filereadstream.h>

QbertGame::QbertGame()
	:m_CurrentDifficulty{1}
	, m_Size{7}
	, m_TileSize{60}
{
	using rapidjson::Document;
	Document jsonDoc;
	FILE* fp = nullptr;
	fopen_s(&fp, "../Data/qbertLevel.json", "rb");

	if (fp != nullptr)
	{
		fseek(fp, 0, SEEK_END);
		size_t size = ftell(fp);
		fseek(fp, 0, SEEK_SET);
		char* readBuffer = new char[size];
		rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));
		jsonDoc.ParseStream(is);
		delete[] readBuffer;
		fclose(fp);

		using rapidjson::Value;

		const Value& difficultyValue = jsonDoc["StartDifficulty"];
		const Value& pyramidSize = jsonDoc["Size"];
		const Value& texture = jsonDoc["Texture"];
		const Value& tileSize = jsonDoc["TileSize"];
		const Value& startLives = jsonDoc["StartLives"];

		m_CurrentDifficulty = difficultyValue.GetInt();
		m_Size = pyramidSize.GetInt();
		m_TileTexture = texture.GetString();
		m_TileSize = tileSize.GetInt();
		m_StartLives = startLives.GetInt();
		m_CurrentLives = m_StartLives;
	}
}

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
	menuComponent->AddObserver(this);

	auto menuUpCommand = new MenuUpCommand();
	menuUpCommand->Bind(menuComponent);
	cri::InputManager::GetInstance().AddKeyboardCommand(sceneIdx, cri::ButtonState::OnPressed, SDL_SCANCODE_KP_8, menuUpCommand);
	menuUpCommand = new MenuUpCommand();
	menuUpCommand->Bind(menuComponent);
	cri::InputManager::GetInstance().AddControllerButtonCommand(0, sceneIdx, cri::ButtonState::OnPressed, cri::ControllerButton::DPadUp, menuUpCommand);

	auto menuDownCommand = new MenuDownCommand();
	menuDownCommand->Bind(menuComponent);
	cri::InputManager::GetInstance().AddKeyboardCommand(sceneIdx, cri::ButtonState::OnPressed, SDL_SCANCODE_KP_2, menuDownCommand);
	menuDownCommand = new MenuDownCommand();
	menuDownCommand->Bind(menuComponent);
	cri::InputManager::GetInstance().AddControllerButtonCommand(0, sceneIdx, cri::ButtonState::OnPressed, cri::ControllerButton::DPadDown, menuDownCommand);

	auto menuClickCommand = new MenuButtonClickCommand();
	menuClickCommand->Bind(menuComponent);
	cri::InputManager::GetInstance().AddKeyboardCommand(sceneIdx, cri::ButtonState::OnPressed, SDL_SCANCODE_RETURN, menuClickCommand);
	menuClickCommand = new MenuButtonClickCommand();
	menuClickCommand->Bind(menuComponent);
	cri::InputManager::GetInstance().AddControllerButtonCommand(0, sceneIdx, cri::ButtonState::OnPressed, cri::ControllerButton::ButtonA, menuClickCommand);

	scene.Add(menu);

}

void QbertGame::CreateLevelScene()
{
	auto& scene = cri::SceneManager::GetInstance().CreateScene("qbert");
	int sceneIdx = cri::SceneManager::GetInstance().GetCurrentSceneIdx();


	///////
	//Qbert

	m_QBert = std::make_shared<cri::GameObject>();
	m_QBert->Deactivate();
	auto qBertTextureComp = new SingleRowAnimationComponent(m_QBert.get(), 4, 2, cri::ResourceManager::GetInstance().LoadTexture("QbertSpriteSheet.png"));
	qBertTextureComp->SetWidth(30.f);
	qBertTextureComp->SetHeight(30.f);
	qBertTextureComp->SetAnimation(2);

	auto qBertJumperComp = new QbertJumperComponent(m_QBert.get());
	scene.Add(m_QBert);
	qBertJumperComp->AddObserver(this);

	auto jumpUpLeftCommand = new JumpCommand(-1, -1);
	jumpUpLeftCommand->Bind(qBertJumperComp);

	cri::InputManager::GetInstance().AddKeyboardCommand(sceneIdx, cri::ButtonState::Down, SDL_Scancode::SDL_SCANCODE_KP_7, jumpUpLeftCommand);

	jumpUpLeftCommand = new JumpCommand(-1, -1);
	jumpUpLeftCommand->Bind(qBertJumperComp);

	cri::InputManager::GetInstance().AddControllerJoystickCommand(0, sceneIdx, 10000, cri::Joystick::Left, cri::JoystickDirection::UpLeft, jumpUpLeftCommand);

	auto jumpUpRightCommand = new JumpCommand(1, -1);
	jumpUpRightCommand->Bind(qBertJumperComp);

	cri::InputManager::GetInstance().AddKeyboardCommand(sceneIdx, cri::ButtonState::Down, SDL_Scancode::SDL_SCANCODE_KP_9, jumpUpRightCommand);

	jumpUpRightCommand = new JumpCommand(1, -1);
	jumpUpRightCommand->Bind(qBertJumperComp);

	cri::InputManager::GetInstance().AddControllerJoystickCommand(0, sceneIdx, 10000, cri::Joystick::Left, cri::JoystickDirection::UpRight, jumpUpRightCommand);

	auto jumpDownLeftCommand = new JumpCommand(-1, 1);
	jumpDownLeftCommand->Bind(qBertJumperComp);

	cri::InputManager::GetInstance().AddKeyboardCommand(sceneIdx, cri::ButtonState::Down, SDL_Scancode::SDL_SCANCODE_KP_1, jumpDownLeftCommand);

	jumpDownLeftCommand = new JumpCommand(-1, 1);
	jumpDownLeftCommand->Bind(qBertJumperComp);

	cri::InputManager::GetInstance().AddControllerJoystickCommand(0, sceneIdx, 10000, cri::Joystick::Left, cri::JoystickDirection::DownLeft, jumpDownLeftCommand);

	auto jumpDownRightCommand = new JumpCommand(1, 1);
	jumpDownRightCommand->Bind(qBertJumperComp);

	cri::InputManager::GetInstance().AddKeyboardCommand(sceneIdx, cri::ButtonState::Down, SDL_Scancode::SDL_SCANCODE_KP_3, jumpDownRightCommand);

	jumpDownRightCommand = new JumpCommand(1, 1);
	jumpDownRightCommand->Bind(qBertJumperComp);

	cri::InputManager::GetInstance().AddControllerJoystickCommand(0, sceneIdx, 10000, cri::Joystick::Left, cri::JoystickDirection::DownRight, jumpDownRightCommand);

	////////
	//Qbert2

	m_QBert2 = std::make_shared<cri::GameObject>();
	m_QBert2->Deactivate();
	qBertTextureComp = new SingleRowAnimationComponent(m_QBert2.get(), 4, 2, cri::ResourceManager::GetInstance().LoadTexture("QbertSpriteSheet.png"));
	qBertTextureComp->SetWidth(30.f);
	qBertTextureComp->SetHeight(30.f);
	qBertTextureComp->SetAnimation(2);

	qBertJumperComp = new QbertJumperComponent(m_QBert2.get());
	scene.Add(m_QBert2);
	qBertJumperComp->AddObserver(this);

	jumpUpLeftCommand = new JumpCommand(-1, -1);
	jumpUpLeftCommand->Bind(qBertJumperComp);

	cri::InputManager::GetInstance().AddKeyboardCommand(sceneIdx, cri::ButtonState::Down, SDL_Scancode::SDL_SCANCODE_Q, jumpUpLeftCommand);

	jumpUpLeftCommand = new JumpCommand(-1, -1);
	jumpUpLeftCommand->Bind(qBertJumperComp);

	cri::InputManager::GetInstance().AddControllerJoystickCommand(1, sceneIdx, 10000, cri::Joystick::Left, cri::JoystickDirection::UpLeft, jumpUpLeftCommand);

	jumpUpRightCommand = new JumpCommand(1, -1);
	jumpUpRightCommand->Bind(qBertJumperComp);

	cri::InputManager::GetInstance().AddKeyboardCommand(sceneIdx, cri::ButtonState::Down, SDL_Scancode::SDL_SCANCODE_E, jumpUpRightCommand);

	jumpUpRightCommand = new JumpCommand(1, -1);
	jumpUpRightCommand->Bind(qBertJumperComp);

	cri::InputManager::GetInstance().AddControllerJoystickCommand(1, sceneIdx, 10000, cri::Joystick::Left, cri::JoystickDirection::UpRight, jumpUpRightCommand);

	jumpDownLeftCommand = new JumpCommand(-1, 1);
	jumpDownLeftCommand->Bind(qBertJumperComp);

	cri::InputManager::GetInstance().AddKeyboardCommand(sceneIdx, cri::ButtonState::Down, SDL_Scancode::SDL_SCANCODE_A, jumpDownLeftCommand);

	jumpDownLeftCommand = new JumpCommand(-1, 1);
	jumpDownLeftCommand->Bind(qBertJumperComp);

	cri::InputManager::GetInstance().AddControllerJoystickCommand(1, sceneIdx, 10000, cri::Joystick::Left, cri::JoystickDirection::DownLeft, jumpDownLeftCommand);

	jumpDownRightCommand = new JumpCommand(1, 1);
	jumpDownRightCommand->Bind(qBertJumperComp);

	cri::InputManager::GetInstance().AddKeyboardCommand(sceneIdx, cri::ButtonState::Down, SDL_Scancode::SDL_SCANCODE_D, jumpDownRightCommand);

	jumpDownRightCommand = new JumpCommand(1, 1);
	jumpDownRightCommand->Bind(qBertJumperComp);

	cri::InputManager::GetInstance().AddControllerJoystickCommand(1, sceneIdx, 10000, cri::Joystick::Left, cri::JoystickDirection::DownRight, jumpDownRightCommand);


	////////
	//Coily

	m_Coily = std::make_shared<cri::GameObject>();
	m_Coily->Deactivate();

	auto coilyTextureComp = new SingleRowAnimationComponent(m_Coily.get(), 4, 2, cri::ResourceManager::GetInstance().LoadTexture("CoilySpriteSheet.png"));
	coilyTextureComp->SetWidth(30.f);
	coilyTextureComp->SetHeight(60.f);
	coilyTextureComp->SetAnimation(2);
	coilyTextureComp->m_RelativeTransform.SetPosition(0.f, -10.f, 0.f);


	auto coilyBallTextureComp = new SingleRowAnimationComponent(m_Coily.get(), 1, 2, cri::ResourceManager::GetInstance().LoadTexture("CoilyBallSpriteSheet.png"));
	coilyBallTextureComp->SetWidth(30.f);
	coilyBallTextureComp->SetHeight(30.f);
	coilyBallTextureComp->SetAnimation(0);
	coilyBallTextureComp->SetIsActive(false);

	auto coilyJumperComponent = new CoilyJumperComponent(m_Coily.get());

	scene.Add(m_Coily);

	jumpUpLeftCommand = new JumpCommand(-1, -1);
	jumpUpLeftCommand->Bind(coilyJumperComponent);

	cri::InputManager::GetInstance().AddKeyboardCommand(sceneIdx, cri::ButtonState::Down, SDL_Scancode::SDL_SCANCODE_Q, jumpUpLeftCommand);

	jumpUpLeftCommand = new JumpCommand(-1, -1);
	jumpUpLeftCommand->Bind(coilyJumperComponent);

	cri::InputManager::GetInstance().AddControllerJoystickCommand(1, sceneIdx, 10000, cri::Joystick::Left, cri::JoystickDirection::UpLeft, jumpUpLeftCommand);

	jumpUpRightCommand = new JumpCommand(1, -1);
	jumpUpRightCommand->Bind(coilyJumperComponent);

	cri::InputManager::GetInstance().AddKeyboardCommand(sceneIdx, cri::ButtonState::Down, SDL_Scancode::SDL_SCANCODE_E, jumpUpRightCommand);

	jumpUpRightCommand = new JumpCommand(1, -1);
	jumpUpRightCommand->Bind(coilyJumperComponent);

	cri::InputManager::GetInstance().AddControllerJoystickCommand(1, sceneIdx, 10000, cri::Joystick::Left, cri::JoystickDirection::UpRight, jumpUpRightCommand);

	jumpDownLeftCommand = new JumpCommand(-1, 1);
	jumpDownLeftCommand->Bind(coilyJumperComponent);

	cri::InputManager::GetInstance().AddKeyboardCommand(sceneIdx, cri::ButtonState::Down, SDL_Scancode::SDL_SCANCODE_A, jumpDownLeftCommand);

	jumpDownLeftCommand = new JumpCommand(-1, 1);
	jumpDownLeftCommand->Bind(coilyJumperComponent);

	cri::InputManager::GetInstance().AddControllerJoystickCommand(1, sceneIdx, 10000, cri::Joystick::Left, cri::JoystickDirection::DownLeft, jumpDownLeftCommand);

	jumpDownRightCommand = new JumpCommand(1, 1);
	jumpDownRightCommand->Bind(coilyJumperComponent);

	cri::InputManager::GetInstance().AddKeyboardCommand(sceneIdx, cri::ButtonState::Down, SDL_Scancode::SDL_SCANCODE_D, jumpDownRightCommand);

	jumpDownRightCommand = new JumpCommand(1, 1);
	jumpDownRightCommand->Bind(coilyJumperComponent);

	cri::InputManager::GetInstance().AddControllerJoystickCommand(1, sceneIdx, 10000, cri::Joystick::Left, cri::JoystickDirection::DownRight, jumpDownRightCommand);



	//fps counter
	auto go = std::make_shared<cri::GameObject>();
	FPSCounterComponent* fpsCounterComponent = new FPSCounterComponent(go.get());
	auto renderCommand = new SwapDoRenderTextCommand();
	renderCommand->Bind(fpsCounterComponent);
	cri::InputManager::GetInstance().AddKeyboardCommand(sceneIdx, cri::ButtonState::OnPressed, SDL_SCANCODE_F, renderCommand);
	renderCommand = new SwapDoRenderTextCommand();
	renderCommand->Bind(fpsCounterComponent);
	cri::InputManager::GetInstance().AddControllerButtonCommand(sceneIdx, 0, cri::ButtonState::OnPressed, cri::ControllerButton::ButtonA, renderCommand);
	scene.Add(go);


}

void QbertGame::SetupLevelSinglePlayer()
{
	cri::SceneManager::GetInstance().NextScene();
	m_CurrentLives = m_StartLives;
	m_SelectedGameMode = GameMode::SinglePlayer;

	auto& scene = cri::SceneManager::GetInstance().GetCurrentScene();

	int w;
	int h;
	SDL_GetWindowSize(cri::Renderer::GetInstance().GetWindow(), &w, &h);
	m_pLevel = new Level{ m_Size, m_CurrentDifficulty, m_TileSize, w / 2.f, h / 4.f, scene, m_TileTexture, this };
	m_QBert->GetComponent<QbertJumperComponent>()->SetStartPos(m_pLevel, 0, 0);
	m_QBert->Activate();
	cri::SceneManager::GetInstance().GetCurrentScene().MoveObjectToFront(m_QBert.get());
	m_QBert2->GetComponent<QbertJumperComponent>()->SetStartPos(m_pLevel, m_Size - 1, 0);
	m_QBert2->Deactivate();
	cri::SceneManager::GetInstance().GetCurrentScene().MoveObjectToFront(m_QBert2.get());
	m_Coily->GetComponent<CoilyJumperComponent>()->SetStartPos(m_pLevel, 0, 0);
	m_Coily->Deactivate();
	cri::SceneManager::GetInstance().GetCurrentScene().MoveObjectToFront(m_Coily.get());

}

void QbertGame::SetupLevelCoop()
{
	cri::SceneManager::GetInstance().NextScene();
	m_CurrentLives = m_StartLives;
	m_SelectedGameMode = GameMode::Coop;

	auto& scene = cri::SceneManager::GetInstance().GetCurrentScene();

	int w;
	int h;
	SDL_GetWindowSize(cri::Renderer::GetInstance().GetWindow(), &w, &h);
	m_pLevel = new Level{ m_Size, m_CurrentDifficulty, m_TileSize, w / 2.f, h / 4.f, scene, m_TileTexture, this };
	m_QBert->GetComponent<QbertJumperComponent>()->SetStartPos(m_pLevel, m_Size-1, m_Size-1);
	m_QBert->Activate();
	cri::SceneManager::GetInstance().GetCurrentScene().MoveObjectToFront(m_QBert.get());
	m_QBert2->GetComponent<QbertJumperComponent>()->SetStartPos(m_pLevel, m_Size - 1, 0);
	m_QBert2->Activate();
	cri::SceneManager::GetInstance().GetCurrentScene().MoveObjectToFront(m_QBert2.get());
	m_Coily->GetComponent<CoilyJumperComponent>()->SetStartPos(m_pLevel, 0, 0);
	m_Coily->Deactivate();
	cri::SceneManager::GetInstance().GetCurrentScene().MoveObjectToFront(m_Coily.get());
}

void QbertGame::SetupLevelVersus()
{
	cri::SceneManager::GetInstance().NextScene();
	m_CurrentLives = m_StartLives;
	m_SelectedGameMode = GameMode::Versus;

	auto& scene = cri::SceneManager::GetInstance().GetCurrentScene();

	int w;
	int h;
	SDL_GetWindowSize(cri::Renderer::GetInstance().GetWindow(), &w, &h);
	m_pLevel = new Level{ m_Size, m_CurrentDifficulty, m_TileSize, w / 2.f, h / 4.f, scene, m_TileTexture, this };
	m_QBert->GetComponent<QbertJumperComponent>()->SetStartPos(m_pLevel, 0, 0);
	m_QBert->Activate();
	cri::SceneManager::GetInstance().GetCurrentScene().MoveObjectToFront(m_QBert.get());
	m_QBert2->GetComponent<QbertJumperComponent>()->SetStartPos(m_pLevel, m_Size - 1, 0);
	m_QBert2->Deactivate();
	cri::SceneManager::GetInstance().GetCurrentScene().MoveObjectToFront(m_QBert2.get());
	m_Coily->GetComponent<CoilyJumperComponent>()->SetStartPos(m_pLevel, 0, 0);
	m_Coily->Activate();
	cri::SceneManager::GetInstance().GetCurrentScene().MoveObjectToFront(m_Coily.get());
}

void QbertGame::OnNotify(Event event)
{
	switch (event)
	{
	case Event::QbertDeath:
		--m_CurrentLives;
		if (m_CurrentLives == 0)
		{
			delete m_pLevel;
			cri::SceneManager::GetInstance().NextScene();
			m_QBert->Deactivate();
			m_QBert2->Deactivate();
		}
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
		SetupLevelSinglePlayer();
		break;
	case Event::StartCoop:
		SetupLevelCoop();
		break;
	case Event::StartVersus:
		SetupLevelVersus();
		break;
	case Event::TileJumpedOn:
		if (m_pLevel->Completed())
		{
			++m_CurrentDifficulty;
			delete m_pLevel;
			switch (m_SelectedGameMode)
			{
			case GameMode::SinglePlayer:
				SetupLevelSinglePlayer();
				break;
			case GameMode::Coop:
				SetupLevelCoop();
				break;
			case GameMode::Versus:
				SetupLevelVersus();
				break;
			default:
				break;
			}
		}
		break;
	default:
		break;
	}
}
