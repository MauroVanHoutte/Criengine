#include "Qbert.h"
#include <InputManager.h>
#include <SceneManager.h>
#include <Scene.h>
#include "HealthCounter.h"
#include "QbertHealthComponent.h"
#include "QbertScoreComponent.h"
#include "QbertCaughtSlickSamCommand.h"
#include "QbertColorChangeCommand.h"
#include "QbertCoilyDeathCommand.h"
#include "QbertRemainingDiscCommand.h"
#include "QbertDeathCommand.h"
#include "ScoreCounter.h"
#include <ServiceLocator.h>

void QbertGame::Init()
{
	auto& scene = cri::SceneManager::GetInstance().CreateScene("Qbert");
	ServiceLocator::GetSoundSystem()->Play("../Data/highlands.wav", 1, 100);

	//Qbert Player1
	const int startHp{ 5 };
	auto Qbert = std::make_shared<cri::GameObject>();
	QbertHealthComponent* healthComponent = new QbertHealthComponent(Qbert.get(), startHp);
	Qbert->AddComponent("HealthComponent", healthComponent);
	QbertScoreComponent* scoreComponent = new QbertScoreComponent(Qbert.get(), 0);
	Qbert->AddComponent("ScoreComponent", scoreComponent);
	scene.Add(Qbert);

	//UI Player1
	auto playerUI = std::make_shared<cri::GameObject>();
	HealthCounter* healthCounterComponent = new HealthCounter{ playerUI.get(), startHp, {80.f, 100.f, 0.f} };
	playerUI->AddComponent("HealthCounter", healthCounterComponent);
	ScoreCounter* scoreCounter = new ScoreCounter{ playerUI.get(), 0, {80.f, 120.f, 0.f} };
	playerUI->AddComponent("ScoreCounter", scoreCounter);
	scene.Add(playerUI);

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
	auto Qbert2 = std::make_shared<cri::GameObject>();
	healthComponent = new QbertHealthComponent(Qbert2.get(), startHp);
	Qbert2->AddComponent("HealthComponent", healthComponent);
	scoreComponent = new QbertScoreComponent(Qbert2.get(), 0);
	Qbert2->AddComponent("ScoreComponent", scoreComponent);
	scene.Add(Qbert2);

	//UI Player2
	auto player2UI = std::make_shared<cri::GameObject>();
	healthCounterComponent = new HealthCounter{ player2UI.get(), startHp, {180.f, 100.f, 0.f} };
	player2UI->AddComponent("HealthCounter", healthCounterComponent);
	scoreCounter = new ScoreCounter{ player2UI.get(), 0, {180.f, 120.f, 0.f} };
	player2UI->AddComponent("ScoreCounter", scoreCounter);
	scene.Add(player2UI);

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