#include "MiniginPCH.h"
#include "QbertScoreComponent.h"

QbertScoreComponent::QbertScoreComponent(dae::GameObject* owner, int startScore)
	:BaseComponent(owner)
	, m_Score(startScore)
{
}

void QbertScoreComponent::ColorChange()
{
	m_Score += 25;
	Notify(Event::ColorChange);
}

void QbertScoreComponent::CoilyDeath()
{
	m_Score += 500;
	Notify(Event::CoilyDeath);
}

void QbertScoreComponent::RemainingDisc()
{
	m_Score += 50;
	Notify(Event::RemainingDisc);
}

void QbertScoreComponent::CaughtSlickSam()
{
	m_Score += 300;
	Notify(Event::SlickSamCaught);
}
