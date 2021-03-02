#include "MiniginPCH.h"
#include "ScoreCounter.h"

ScoreCounter::ScoreCounter(dae::GameObject* owner, int startScore, glm::vec3 pos)
	:TextComponent(owner, "", "CamingoCode.ttf", 12,  pos, { 255.f, 0.f, 0.f })
	, m_Score(startScore)
{
	std::string text{ "Score: " };
	text += std::to_string(m_Score);
	SetText(text);
}

void ScoreCounter::OnNotify(Event event)
{
	bool change{ false };
	switch (event)
	{
	case Event::ColorChange:
		m_Score += 25;
		change = true;
		break;
	case Event::CoilyDeath:
		m_Score += 500;
		change = true;
		break;
	case Event::RemainingDisc:
		m_Score += 50;
		change = true;
		break;
	case Event::SlickSamCaught:
		m_Score += 300;
		change = true;
		break;
	}

	if (change)
	{
		std::string text{ "Score: " };
		text += std::to_string(m_Score);
		SetText(text);
	}
}
