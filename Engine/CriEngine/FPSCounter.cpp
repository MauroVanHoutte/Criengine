#include "FPSCounter.h"
#include "Timer.h"


FPSCounterComponent::FPSCounterComponent(cri::GameObject* owner)
	: TextComponent(owner, "fps : 0", "CamingoCode.ttf", 12, { 5.f, 5.f }, { 255.f, 0.f, 0.f })
	, m_Elapsed{0.0f}
	, m_FrameCounter{0}
{
}

void FPSCounterComponent::Update()
{
	m_Elapsed += Timer::GetInstance()->GetElapsed();
	++m_FrameCounter;

	if (m_Elapsed > 1.f)
	{
		std::string text{ "Fps : " };
		text += std::to_string(m_FrameCounter);
		text += "\nUpdateTime : ";
		text += std::to_string(Timer::GetInstance()->GetUpdateTime()*1000);
		text += "ms\nRenderTime : ";
		text += std::to_string(int(Timer::GetInstance()->GetRenderTime()*1000));
		text += "ms";
		SetText(text);

		m_Elapsed -= 1.f;
		m_FrameCounter = 0;
	}
}

