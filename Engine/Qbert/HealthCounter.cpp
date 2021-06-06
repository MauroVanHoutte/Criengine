#include "HealthCounter.h"
#include <glm/vec3.hpp>

HealthCounter::HealthCounter(cri::GameObject* owner, int startHP, glm::vec2 pos)
	: TextComponent(owner, "", "CamingoCode.ttf", 12, { pos }, { 255.f, 0.f, 0.f })
	, m_Health{startHP}
	, m_StartHp{startHP}
{
	std::string text{ "Health: " };
	text += std::to_string(m_Health);
	SetText(text);
}

void HealthCounter::OnNotify(Event event)
{
	if (event == Event::QbertDeath)
	{
		--m_Health;
		std::string text{"Health: "};
		text += std::to_string(m_Health);
		SetText(text);
	}
	if (event == Event::GameStart)
	{
		m_Health = m_StartHp;
		std::string text{ "Health: " };
		text += std::to_string(m_Health);
		SetText(text);
	}
}
