#pragma once
#include "BaseJumperComponent.h"

class QbertJumperComponent : public BaseJumperComponent
{
public:
	QbertJumperComponent(cri::GameObject* pOwner);
	QbertJumperComponent() = delete;

	void JumpedOff() override;

	void HandleAnimation(int colDir, int rowDir) override;

	void HandleStartPos(std::shared_ptr<cri::GameObject> target) override;

	void JumpedOn() override;

private:
};