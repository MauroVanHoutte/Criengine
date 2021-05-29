#pragma once
#include "Observer.h"
#include <memory>
#include <GameObject.h>

enum class GameMode
{
	SinglePlayer,
	Coop,
	Versus
};

class Level;
class QbertGame : public Observer
{
public:
	QbertGame();

	void Init();
	void Cleanup();

	void CreateMenuScene();
	void CreateLevelScene();

	void SetupLevelSinglePlayer();
	void SetupLevelCoop();
	void SetupLevelVersus();

	void OnNotify(Event event) override;

private:

	Level* m_pLevel = nullptr;
	std::shared_ptr<cri::GameObject> m_QBert = nullptr;
	std::shared_ptr<cri::GameObject> m_QBert2 = nullptr;
	std::shared_ptr<cri::GameObject> m_Coily = nullptr;
	int m_CurrentDifficulty;
	std::string m_TileTexture;
	int m_Size;
	int m_TileSize;
	int m_StartLives;
	int m_CurrentLives;
	GameMode m_SelectedGameMode;
};