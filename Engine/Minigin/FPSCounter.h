#pragma once
#include "BaseComponent.h"
#include "TextComponent.h"

class FPSCounterComponent : public BaseComponent
{
public:
	FPSCounterComponent(dae::GameObject* owner);
	virtual ~FPSCounterComponent() = default;

	void Update() override;
	void Render() const override;

private:
	float m_Elapsed;
	int m_FrameCounter;
	TextComponent m_TextComponent;
};