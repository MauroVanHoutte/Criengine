#include "HealthCounter.h"

HealthCounter::HealthCounter(cri::GameObject* owner, int startHP, glm::vec3 pos)
	: TextComponent(owner, "", "CamingoCode.ttf", 12, { pos }, { 255.f, 0.f, 0.f })
	, m_Health{startHP}
{
	std::string text{ "Health: " };
	text += std::to_string(m_Health);
	SetText(text);
}

void HealthCounter::OnNotify(Event event)
{
	if (event == Event::PlayerDeath)
	{
		--m_Health;
		std::string text{"Health: "};
		text += std::to_string(m_Health);
		SetText(text);
	}
}
