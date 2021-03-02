#pragma once
#include "BaseComponent.h"
#include "Subject.h"

class QbertScoreComponent : public BaseComponent, public Subject
{
public:
	QbertScoreComponent(dae::GameObject* owner, int startScore);

	void ColorChange();
	void CoilyDeath();
	void RemainingDisc();
	void CaughtSlickSam();
private:
	int m_Score;
};