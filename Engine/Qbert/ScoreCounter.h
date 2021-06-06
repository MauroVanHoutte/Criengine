#pragma once
#include "TextComponent.h"
#include "Observer.h"

class ScoreCounter : public TextComponent, public Observer
{
public:
	ScoreCounter(cri::GameObject* owner, int startScore, glm::vec2 pos);
	void OnNotify(Event event) override;

private:
	int m_Score;
};