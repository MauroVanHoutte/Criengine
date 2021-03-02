#pragma once
#include "BaseComponent.h"
#include "Subject.h"

class QbertHealthComponent : public BaseComponent, public Subject
{
public:
	QbertHealthComponent(dae::GameObject* owner, int startHP);

	void Death();
private:
	int m_Health;
};
