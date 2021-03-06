#include "Qbert.h"
#include <InputManager.h>
#include <SceneManager.h>
#include <Scene.h>
#include "HealthCounter.h"
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
#include <rapidjson.h>
#include <document.h>
#include <filereadstream.h>
#include "SpawnerComponent.h"
#include "BaseColliderComponent.h"

QbertGame::QbertGame()
	:m_CurrentDifficulty{1}
	, m_Size{7}
	, m_TileSize{60}
	, m_StartLives{3}
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

		m_CurrentDifficulty = difficultyValue.GetInt();
		m_Size = pyramidSize.GetInt();
		m_TileTexture = texture.GetString();
		m_TileSize = tileSize.GetInt();
		m_CurrentLives = m_StartLives;
	}
}

void QbertGame::Init()
{
	
}

void QbertGame::Cleanup()
{
	if (m_pLevel != nullptr)
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
	menu->m_Transform.SetPosition(float(2.f*screenW/5.f), float(screenH/2.f));
	auto menuComponent = new QbertMainMenuComponent(menu.get());
	menuComponent->AddObserver(this);

	auto menuUpCommand = std::make_shared<MenuUpCommand>();
	menuUpCommand->Bind(menuComponent);
	cri::InputManager::GetInstance().AddKeyboardCommand(sceneIdx, cri::ButtonState::OnPressed, SDL_SCANCODE_KP_8, menuUpCommand);
	cri::InputManager::GetInstance().AddControllerButtonCommand(0, sceneIdx, cri::ButtonState::OnPressed, cri::ControllerButton::DPadUp, menuUpCommand);

	auto menuDownCommand =  std::make_shared<MenuDownCommand>();
	menuDownCommand->Bind(menuComponent);
	cri::InputManager::GetInstance().AddKeyboardCommand(sceneIdx, cri::ButtonState::OnPressed, SDL_SCANCODE_KP_2, menuDownCommand);
	cri::InputManager::GetInstance().AddControllerButtonCommand(0, sceneIdx, cri::ButtonState::OnPressed, cri::ControllerButton::DPadDown, menuDownCommand);

	auto menuClickCommand =  std::make_shared<MenuButtonClickCommand>();
	menuClickCommand->Bind(menuComponent);
	cri::InputManager::GetInstance().AddKeyboardCommand(sceneIdx, cri::ButtonState::OnPressed, SDL_SCANCODE_RETURN, menuClickCommand);
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

	new BaseColliderComponent(m_QBert.get(), 15.f, 15.f, Type::Qbert);

	auto qBertJumperComp = new QbertJumperComponent(m_QBert.get());
	scene.Add(m_QBert);
	qBertJumperComp->AddObserver(this);

	auto jumpUpLeftCommand = std::make_shared<JumpCommand>(-1, -1);
	jumpUpLeftCommand->Bind(qBertJumperComp);

	cri::InputManager::GetInstance().AddKeyboardCommand(sceneIdx, cri::ButtonState::Down, SDL_Scancode::SDL_SCANCODE_KP_7, jumpUpLeftCommand);
	cri::InputManager::GetInstance().AddControllerJoystickCommand(0, sceneIdx, 10000, cri::Joystick::Left, cri::JoystickDirection::UpLeft, jumpUpLeftCommand);

	auto jumpUpRightCommand = std::make_shared<JumpCommand>(1, -1);
	jumpUpRightCommand->Bind(qBertJumperComp);

	cri::InputManager::GetInstance().AddKeyboardCommand(sceneIdx, cri::ButtonState::Down, SDL_Scancode::SDL_SCANCODE_KP_9, jumpUpRightCommand);
	cri::InputManager::GetInstance().AddControllerJoystickCommand(0, sceneIdx, 10000, cri::Joystick::Left, cri::JoystickDirection::UpRight, jumpUpRightCommand);

	auto jumpDownLeftCommand = std::make_shared<JumpCommand>(-1, 1);
	jumpDownLeftCommand->Bind(qBertJumperComp);

	cri::InputManager::GetInstance().AddKeyboardCommand(sceneIdx, cri::ButtonState::Down, SDL_Scancode::SDL_SCANCODE_KP_1, jumpDownLeftCommand);
	cri::InputManager::GetInstance().AddControllerJoystickCommand(0, sceneIdx, 10000, cri::Joystick::Left, cri::JoystickDirection::DownLeft, jumpDownLeftCommand);

	auto jumpDownRightCommand = std::make_shared<JumpCommand>(1, 1);
	jumpDownRightCommand->Bind(qBertJumperComp);

	cri::InputManager::GetInstance().AddKeyboardCommand(sceneIdx, cri::ButtonState::Down, SDL_Scancode::SDL_SCANCODE_KP_3, jumpDownRightCommand);
	cri::InputManager::GetInstance().AddControllerJoystickCommand(0, sceneIdx, 10000, cri::Joystick::Left, cri::JoystickDirection::DownRight, jumpDownRightCommand);

	////////
	//Qbert2

	m_QBert2 = std::make_shared<cri::GameObject>();
	m_QBert2->Deactivate();
	qBertTextureComp = new SingleRowAnimationComponent(m_QBert2.get(), 4, 2, cri::ResourceManager::GetInstance().LoadTexture("QbertSpriteSheet.png"));
	qBertTextureComp->SetWidth(30.f);
	qBertTextureComp->SetHeight(30.f);
	qBertTextureComp->SetAnimation(2);

	new BaseColliderComponent(m_QBert2.get(), 15.f, 15.f, Type::Qbert);

	qBertJumperComp = new QbertJumperComponent(m_QBert2.get());
	scene.Add(m_QBert2);
	qBertJumperComp->AddObserver(this);

	jumpUpLeftCommand = std::make_shared<JumpCommand>(-1, -1);
	jumpUpLeftCommand->Bind(qBertJumperComp);

	cri::InputManager::GetInstance().AddKeyboardCommand(sceneIdx, cri::ButtonState::Down, SDL_Scancode::SDL_SCANCODE_Q, jumpUpLeftCommand);
	cri::InputManager::GetInstance().AddControllerJoystickCommand(1, sceneIdx, 10000, cri::Joystick::Left, cri::JoystickDirection::UpLeft, jumpUpLeftCommand);

	jumpUpRightCommand = std::make_shared<JumpCommand>(1, -1);
	jumpUpRightCommand->Bind(qBertJumperComp);

	cri::InputManager::GetInstance().AddKeyboardCommand(sceneIdx, cri::ButtonState::Down, SDL_Scancode::SDL_SCANCODE_E, jumpUpRightCommand);
	cri::InputManager::GetInstance().AddControllerJoystickCommand(1, sceneIdx, 10000, cri::Joystick::Left, cri::JoystickDirection::UpRight, jumpUpRightCommand);

	jumpDownLeftCommand = std::make_shared<JumpCommand>(-1, 1);
	jumpDownLeftCommand->Bind(qBertJumperComp);

	cri::InputManager::GetInstance().AddKeyboardCommand(sceneIdx, cri::ButtonState::Down, SDL_Scancode::SDL_SCANCODE_A, jumpDownLeftCommand);
	cri::InputManager::GetInstance().AddControllerJoystickCommand(1, sceneIdx, 10000, cri::Joystick::Left, cri::JoystickDirection::DownLeft, jumpDownLeftCommand);

	jumpDownRightCommand = std::make_shared<JumpCommand>(1, 1);
	jumpDownRightCommand->Bind(qBertJumperComp);

	cri::InputManager::GetInstance().AddKeyboardCommand(sceneIdx, cri::ButtonState::Down, SDL_Scancode::SDL_SCANCODE_D, jumpDownRightCommand);
	cri::InputManager::GetInstance().AddControllerJoystickCommand(1, sceneIdx, 10000, cri::Joystick::Left, cri::JoystickDirection::DownRight, jumpDownRightCommand);

	

	////////
	//Spawner

	m_Spawner = std::make_shared<cri::GameObject>();
	new SpawnerComponent(m_Spawner.get(), this);
	scene.Add(m_Spawner);


	///////////
	//fps counter
	auto fpsObject = std::make_shared<cri::GameObject>();
	FPSCounterComponent* fpsCounterComponent = new FPSCounterComponent(fpsObject.get());
	auto renderCommand = std::make_shared<SwapDoRenderTextCommand>();
	renderCommand->Bind(fpsCounterComponent);
	cri::InputManager::GetInstance().AddKeyboardCommand(sceneIdx, cri::ButtonState::OnPressed, SDL_SCANCODE_F, renderCommand);
	cri::InputManager::GetInstance().AddControllerButtonCommand(sceneIdx, 0, cri::ButtonState::OnPressed, cri::ControllerButton::ButtonA, renderCommand);
	scene.Add(fpsObject);


	///////////
	//ui

	auto uiObject = std::make_shared<cri::GameObject>();
	auto scoreUi = new ScoreCounter(uiObject.get(), 0, { 5, 60 });
	auto healthUi = new HealthCounter(uiObject.get(), 3, { 5, 80 });
	AddObserver(scoreUi);
	AddObserver(healthUi);
	m_QBert->GetComponent<BaseColliderComponent>()->AddObserver(scoreUi);
	m_QBert2->GetComponent<BaseColliderComponent>()->AddObserver(scoreUi);
	scene.Add(uiObject);
	
}

void QbertGame::SetupLevelSinglePlayer()
{
	m_CurrentLives = m_StartLives;
	m_SelectedGameMode = GameMode::SinglePlayer;

	auto& scene = cri::SceneManager::GetInstance().GetCurrentScene();

	int w;
	int h;
	SDL_GetWindowSize(cri::Renderer::GetInstance().GetWindow(), &w, &h);
	m_pLevel = new Level{ m_Size, m_CurrentDifficulty, m_TileSize, w / 2.f, h / 4.f, (std::rand() % (m_Size - 2)) + 1, (std::rand() % (m_Size - 2)) + 1, scene, m_TileTexture, this };
	m_QBert->GetComponent<QbertJumperComponent>()->SetStartPos(m_pLevel, 0, 0);
	m_QBert->Activate();
	cri::SceneManager::GetInstance().GetCurrentScene().MoveObjectToFront(m_QBert.get());

	m_QBert2->Deactivate();

	m_Spawner->GetComponent<SpawnerComponent>()->SetCoilyPlayerController(false);


}

void QbertGame::SetupLevelCoop()
{
	m_CurrentLives = m_StartLives;
	m_SelectedGameMode = GameMode::Coop;

	auto& scene = cri::SceneManager::GetInstance().GetCurrentScene();

	int w;
	int h;
	SDL_GetWindowSize(cri::Renderer::GetInstance().GetWindow(), &w, &h);
	m_pLevel = new Level{ m_Size, m_CurrentDifficulty, m_TileSize, w / 2.f, h / 4.f, (std::rand()%(m_Size-2))+1, (std::rand() % (m_Size - 2)) + 1, scene, m_TileTexture, this };
	m_QBert->GetComponent<QbertJumperComponent>()->SetStartPos(m_pLevel, m_Size-1, m_Size-1);
	m_QBert->Activate();
	cri::SceneManager::GetInstance().GetCurrentScene().MoveObjectToFront(m_QBert.get());

	m_QBert2->GetComponent<QbertJumperComponent>()->SetStartPos(m_pLevel, m_Size - 1, 0);
	m_QBert2->Activate();
	cri::SceneManager::GetInstance().GetCurrentScene().MoveObjectToFront(m_QBert2.get());

	m_Spawner->GetComponent<SpawnerComponent>()->SetCoilyPlayerController(false);

}

void QbertGame::SetupLevelVersus()
{
	m_CurrentLives = m_StartLives;
	m_SelectedGameMode = GameMode::Versus;

	auto& scene = cri::SceneManager::GetInstance().GetCurrentScene();

	int w;
	int h;
	SDL_GetWindowSize(cri::Renderer::GetInstance().GetWindow(), &w, &h);
	m_pLevel = new Level{ m_Size, m_CurrentDifficulty, m_TileSize, w / 2.f, h / 4.f, (std::rand() % (m_Size - 2)) + 1, (std::rand() % (m_Size - 2)) + 1, scene, m_TileTexture, this };
	m_QBert->GetComponent<QbertJumperComponent>()->SetStartPos(m_pLevel, 0, 0);
	m_QBert->Activate();
	cri::SceneManager::GetInstance().GetCurrentScene().MoveObjectToFront(m_QBert.get());

	m_QBert2->Deactivate();

	m_Spawner->GetComponent<SpawnerComponent>()->SetCoilyPlayerController(true);
}

Level* QbertGame::GetLevel()
{
	return m_pLevel;
}

void QbertGame::OnNotify(Event event)
{
	switch (event)
	{
	case Event::QbertDeath:
		--m_CurrentLives;
		Notify(Event::QbertDeath);
		m_Spawner->GetComponent<SpawnerComponent>()->ResetAll();
		if (m_CurrentLives == 0)
		{
			m_CurrentDifficulty = 1;
			delete m_pLevel;
			m_pLevel = nullptr;
			cri::SceneManager::GetInstance().NextScene();
		}
		break;
	case Event::CoilyDeath:
		Notify(Event::CoilyDeath);
		break;
	case Event::SlickSamCaught:
		Notify(Event::SlickSamCaught);
		break;
	case Event::StartSinglePlayer:
		Notify(Event::GameStart);
		cri::SceneManager::GetInstance().NextScene();
		SetupLevelSinglePlayer();
		break;
	case Event::StartCoop:
		Notify(Event::GameStart);
		cri::SceneManager::GetInstance().NextScene();
		SetupLevelCoop();
		break;
	case Event::StartVersus:
		Notify(Event::GameStart);
		cri::SceneManager::GetInstance().NextScene();
		SetupLevelVersus();
		break;
	case Event::ColorChange:
		Notify(Event::ColorChange);
		if (m_pLevel->Completed())
		{
			int activeDisks = m_pLevel->NrActiveDisks();

			for (int i = 0; i < activeDisks; i++)
			{
				Notify(Event::RemainingDisc);
			}

			++m_CurrentDifficulty;
			if (m_CurrentDifficulty > 4)
			{
				m_CurrentDifficulty = 4;
			}
			m_Spawner->GetComponent<SpawnerComponent>()->SetDifficulty(m_CurrentDifficulty);
			delete m_pLevel;
			m_pLevel = nullptr;
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
			m_Spawner->GetComponent<SpawnerComponent>()->ResetAll();
		}
		break;
	default:
		break;
	}
}

std::shared_ptr<cri::GameObject> QbertGame::GetQbert1()
{
	return m_QBert;
}

std::shared_ptr<cri::GameObject> QbertGame::GetQbert2()
{
	return m_QBert2;
}
