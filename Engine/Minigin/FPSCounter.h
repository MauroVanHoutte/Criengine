#pragma once
#include "TextComponent.h"

class FPSCounterComponent : public TextComponent
{
public:
	FPSCounterComponent(dae::GameObject* owner);
	virtual ~FPSCounterComponent() = default;

	void Update() override;

private:
	float m_Elapsed;
	int m_FrameCounter;
};