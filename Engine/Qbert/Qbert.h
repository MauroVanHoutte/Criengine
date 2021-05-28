#pragma once
#include "Observer.h"
#include <memory>
#include <GameObject.h>

class Level;
class QbertGame : public Observer
{
public:
	QbertGame();

	void Init();
	void Cleanup();

	void CreateMenuScene();
	void CreateLevelScene();

	void SetupLevel();

	void OnNotify(Event event) override;

private:

	Level* m_pLevel = nullptr;
	std::shared_ptr<cri::GameObject> m_QBert = nullptr;
	int m_CurrentDifficulty;
	std::string m_TileTexture;
	int m_Size;

};