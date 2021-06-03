#pragma once
#include "BaseJumperComponent.h"

class UggWrongwayJumperComponent : public BaseJumperComponent
{
public:
	UggWrongwayJumperComponent(cri::GameObject* owner);

	void Update() override;

	void HandleStartPos() override;

	void JumpedOff() override;

	void HandleAnimation(int coldir, int rowdir) override;

	void SetGoingRight(bool goingRight);
	bool GetGoingRight();

private:
	float m_PauseDuration = 0.2f;
	float m_PauseCounter = 0.f;
	bool m_GoingRight;
};
