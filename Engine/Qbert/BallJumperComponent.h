#pragma once
#include "BaseJumperComponent.h"

class BallJumperComponent : public BaseJumperComponent
{
public:
	BallJumperComponent(cri::GameObject* owner);

	void Update() override;

	void Spawn(cri::GameObject* target);
	void HandleAnimation(int colDir, int rowDir) override;

	void JumpedOff() override;
private:
	float m_PauseDuration = 0.2f;
	float m_PauseCounter = 0.f;
};