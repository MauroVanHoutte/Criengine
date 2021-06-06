#pragma once
#include "TextComponent.h"
#include "Observer.h"

class HealthCounter : public TextComponent, public Observer
{
public:
	HealthCounter(cri::GameObject* owner, int startHp, glm::vec2 pos);
	virtual void OnNotify(Event event) override;

private:
	int m_Health;
	int m_StartHp;
};