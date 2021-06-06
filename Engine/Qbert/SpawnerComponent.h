#pragma once
#include "BaseComponent.h"
#include <memory>
class QbertGame;
class SpawnerComponent : public BaseComponent
{
public:
	SpawnerComponent(cri::GameObject* pOwner, QbertGame* gameManager);

	void CreateGameObjects();

	void Update() override;

	void SetCoilyPlayerController(bool playerControlled);

	void SetDifficulty(int difficulty);

	void SpawnBall();
	void SpawnGreenCreature();
	void SpawnPurpleCreature();
	void SpawnCoily();

	void ResetAll();

private:
	std::vector<cri::GameObject*> m_RedBallVector;
	std::vector<cri::GameObject*> m_PurpleCreatureVector;
	std::vector<cri::GameObject*> m_GreenCreatureVector;
	std::shared_ptr<cri::GameObject> m_Coily;

	float m_BallSpawnInterval = 4.f;
	float m_BallSpawnCounter = 0.f;

	float m_GreenSpawnInerval = 7.f;
	float m_GreenSpawnCounter = 3.5f;

	float m_PurpleSpawnInterval = 7.f;
	float m_PurpleSpawnCounter = 0.f;

	float m_CoilySpawnDelay = 1.f;
	float m_CoilySpawnCounter = 0.f;

	QbertGame* m_GameManager;

	int m_Difficulty;
};
