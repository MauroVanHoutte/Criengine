#pragma once
#include "BaseJumperComponent.h"

class CoilyJumperComponent : public BaseJumperComponent
{
public:
	CoilyJumperComponent(cri::GameObject* owner);
	CoilyJumperComponent() = delete;

	void HandleAnimation(int colDir, int rowDir) override;

	void JumpedOff() override;

	void HandleStartPos() override;

private:

};