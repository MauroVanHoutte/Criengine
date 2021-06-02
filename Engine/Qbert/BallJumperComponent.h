#pragma once
#include "BaseJumperComponent.h"

class BallJumperComponent : public BaseJumperComponent
{
public:
	BallJumperComponent(cri::GameObject* owner);
	void Spawn(cri::GameObject* target);
	void HandleAnimation(int colDir, int rowDir) override;
private:

};