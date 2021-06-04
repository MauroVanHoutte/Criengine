#pragma once
#include "BaseComponent.h"
class QbertGame;
class SpawnerComponent : public BaseComponent
{
public:
	SpawnerComponent(cri::GameObject* pOwner, QbertGame* gameManager);

	void CreateGameObjects();

	void Update() override;

	void SpawnBall();
	void SpawnGreenCreature();
	void SpawnPurpleCreature();

	void ResetAll();

private:
	std::vector<cri::GameObject*> m_RedBallVector;
	std::vector<cri::GameObject*> m_PurpleCreatureVector;
	std::vector<cri::GameObject*> m_GreenCreatureVector;

	float m_BallSpawnInterval = 2.5f;
	float m_BallSpawnCounter = 0.f;

	float m_GreenSpawnInerval = 7.f;
	float m_GreenSpawnCounter = 3.5f;

	float m_PurpleSpawnInterval = 7.f;
	float m_PurpleSpawnCounter = 0.f;

	QbertGame* m_GameManager;
};