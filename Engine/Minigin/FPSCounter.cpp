#include "MiniginPCH.h"
#include "FPSCounter.h"
#include "Timer.h"


FPSCounterComponent::FPSCounterComponent(dae::GameObject* owner)
	: BaseComponent(owner)
	, m_TextComponent(owner, "fps : 0", "Lingua.otf", 12, { 5.f, 5.f, 0.f })
	, m_Elapsed{0.0f}
	, m_FrameCounter{0}
{
}

void FPSCounterComponent::Update()
{
	m_Elapsed += Timer::GetElapsed();
	++m_FrameCounter;

	if (m_Elapsed > 1.f)
	{
		std::string text{ "fps : " };
		text += std::to_string(m_FrameCounter);
		m_TextComponent.SetText(text);

		m_Elapsed -= 1.f;
		m_FrameCounter = 0;
	}
}

void FPSCounterComponent::Render() const
{
	m_TextComponent.Render();
}
