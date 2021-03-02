#pragma once
#include "GameObject.h"
#include <vector>

class QbertGame
{
public:
	QbertGame() = default;
	~QbertGame();

	void Init();

	void Update();
	void LateUpdate();
	void FixedUpdate();
	void Render();

private:
	std::vector<dae::GameObject*> m_GameObjects;
};