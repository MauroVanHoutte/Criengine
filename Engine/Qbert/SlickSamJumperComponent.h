#pragma once
#include "BaseJumperComponent.h"
#include "Subject.h"

class SlickSamJumperComponent : public BaseJumperComponent
{
public:
	SlickSamJumperComponent(cri::GameObject* owner);

	void Update() override;

	void HandleAnimation(int colDir, int rowDir) override;

	void HandleStartPos() override;

	void JumpedOff() override;

	void JumpedOn() override;
private:
	float m_PauseDuration = 0.2f;
	float m_PauseCounter = 0.f;
};