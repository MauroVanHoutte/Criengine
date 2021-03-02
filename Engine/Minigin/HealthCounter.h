#pragma once
#include "TextComponent.h"
#include "Observer.h"

class HealthCounter : public TextComponent, public Observer
{
public:
	HealthCounter(dae::GameObject* owner, int startHp, glm::vec3 pos);
	virtual void OnNotify(Event event) override;

private:
	int m_Health;
};