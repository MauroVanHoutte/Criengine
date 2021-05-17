#include "QbertGame.h"
#include "InputManager.h"
#include "HealthCounter.h"
#include "QbertHealthComponent.h"
#include "QbertScoreComponent.h"
#include "QbertCaughtSlickSamCommand.h"
#include "QbertColorChangeCommand.h"
#include "QbertCoilyDeathCommand.h"
#include "QbertRemainingDiscCommand.h"
#include "QbertDeathCommand.h"
#include "ScoreCounter.h"

QbertGame::~QbertGame()
{
	for (auto it = m_GameObjects.begin(); it != m_GameObjects.end(); ++it)
	{
		delete* it;
		*it = nullptr;
	}
}

void QbertGame::Init()
{
	//Qbert Player1
	const int startHp{ 5 };
	cri::GameObject* Qbert = new cri::GameObject();
	m_GameObjects.push_back(Qbert);
	QbertHealthComponent* healthComponent = new QbertHealthComponent(Qbert, startHp);
	Qbert->AddComponent("HealthComponent", healthComponent);
	QbertScoreComponent* scoreComponent = new QbertScoreComponent(Qbert, 0);
	Qbert->AddComponent("ScoreComponent", scoreComponent);

	//UI Player1
	cri::GameObject* playerUI = new cri::GameObject();
	m_GameObjects.push_back(playerUI);
	HealthCounter* healthCounterComponent = new HealthCounter{ playerUI, startHp, {80.f, 100.f, 0.f} };
	playerUI->AddComponent("HealthCounter", healthCounterComponent);
	ScoreCounter* scoreCounter = new ScoreCounter{ playerUI, 0, {80.f, 120.f, 0.f} };
	playerUI->AddComponent("ScoreCounter", scoreCounter);

	//counter observes the health component
	healthComponent->AddObserver(healthCounterComponent);
	scoreComponent->AddObserver(scoreCounter);

	//Death by controller
	QbertDeathCommand* deathCommand = new QbertDeathCommand(healthComponent);
	cri::InputManager::GetInstance().AddControllerCommand(0, cri::ButtonState::OnPressed, cri::ControllerButton::DPadDown, deathCommand);

	//Score by Controller
	QbertColorChangeCommand* colorCommand = new QbertColorChangeCommand(scoreComponent);
	cri::InputManager::GetInstance().AddControllerCommand(0, cri::ButtonState::OnPressed, cri::ControllerButton::ButtonA, colorCommand);
	QbertCoilyDeathCommand* coilyDeathCommand = new QbertCoilyDeathCommand(scoreComponent);
	cri::InputManager::GetInstance().AddControllerCommand(0, cri::ButtonState::OnPressed, cri::ControllerButton::ButtonB, coilyDeathCommand);
	QbertCaughtSlickSamCommand* caughtSlickSamCommand = new QbertCaughtSlickSamCommand(scoreComponent);
	cri::InputManager::GetInstance().AddControllerCommand(0, cri::ButtonState::OnPressed, cri::ControllerButton::ButtonX, caughtSlickSamCommand);
	QbertRemainingDiscCommand* remainingDiscCommand = new QbertRemainingDiscCommand(scoreComponent);
	cri::InputManager::GetInstance().AddControllerCommand(0, cri::ButtonState::OnPressed, cri::ControllerButton::ButtonY, remainingDiscCommand);
	


	//Qbert Player2
	Qbert = new cri::GameObject();
	m_GameObjects.push_back(Qbert);
	healthComponent = new QbertHealthComponent(Qbert, startHp);
	Qbert->AddComponent("HealthComponent", healthComponent);
	scoreComponent = new QbertScoreComponent(Qbert, 0);
	Qbert->AddComponent("ScoreComponent", scoreComponent);

	//UI Player2
	playerUI = new cri::GameObject();
	m_GameObjects.push_back(playerUI);
	healthCounterComponent = new HealthCounter{ playerUI, startHp, {180.f, 100.f, 0.f} };
	playerUI->AddComponent("HealthCounter", healthCounterComponent);
	scoreCounter = new ScoreCounter{ playerUI, 0, {180.f, 120.f, 0.f} };
	playerUI->AddComponent("ScoreCounter", scoreCounter);

	//counter observes the health component
	healthComponent->AddObserver(healthCounterComponent);
	scoreComponent->AddObserver(scoreCounter);

	//Death by controller
	deathCommand = new QbertDeathCommand(healthComponent);
	cri::InputManager::GetInstance().AddControllerCommand(1, cri::ButtonState::OnPressed, cri::ControllerButton::DPadDown, deathCommand);

	//Score by Controller
	colorCommand = new QbertColorChangeCommand(scoreComponent);
	cri::InputManager::GetInstance().AddControllerCommand(1, cri::ButtonState::OnPressed, cri::ControllerButton::ButtonA, colorCommand);
	coilyDeathCommand = new QbertCoilyDeathCommand(scoreComponent);
	cri::InputManager::GetInstance().AddControllerCommand(1, cri::ButtonState::OnPressed, cri::ControllerButton::ButtonB, coilyDeathCommand);
	caughtSlickSamCommand = new QbertCaughtSlickSamCommand(scoreComponent);
	cri::InputManager::GetInstance().AddControllerCommand(1, cri::ButtonState::OnPressed, cri::ControllerButton::ButtonX, caughtSlickSamCommand);
	remainingDiscCommand = new QbertRemainingDiscCommand(scoreComponent);
	cri::InputManager::GetInstance().AddControllerCommand(1, cri::ButtonState::OnPressed, cri::ControllerButton::ButtonY, remainingDiscCommand);
	
	
	
}

void QbertGame::Update()
{
	for (auto it = m_GameObjects.begin(); it != m_GameObjects.end(); ++it)
	{
		(*it)->Update();
	}
}

void QbertGame::LateUpdate()
{
	for (auto it = m_GameObjects.begin(); it != m_GameObjects.end(); ++it)
	{
		(*it)->LateUpdate();
	}
}

void QbertGame::FixedUpdate()
{
	for (auto it = m_GameObjects.begin(); it != m_GameObjects.end(); ++it)
	{
		(*it)->FixedUpdate();
	}
}

void QbertGame::Render()
{
	for (auto it = m_GameObjects.begin(); it != m_GameObjects.end(); ++it)
	{
		(*it)->Render();
	}
}
