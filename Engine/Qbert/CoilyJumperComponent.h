#pragma once
#include "BaseJumperComponent.h"

class CoilyJumperComponent : public BaseJumperComponent
{
public:
	CoilyJumperComponent(cri::GameObject* owner);
	CoilyJumperComponent() = delete;


	void Update() override;


	void HandleAnimation(int colDir, int rowDir) override;

	void JumpedOff() override;

	void HandleStartPos() override;

	void SetIsPlayerControlled(bool isPlayerControlled);

private:
	bool m_IsEgg{ true };
	bool m_IsPlayerControlled{ false };
	float m_JumpInterval = 0.2f;
	float m_JumpCounter = 0.f;

};