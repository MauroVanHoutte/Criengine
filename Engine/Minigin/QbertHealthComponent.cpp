#include "MiniginPCH.h"
#include "QbertHealthComponent.h"

QbertHealthComponent::QbertHealthComponent(dae::GameObject* owner, int startHP)
	: BaseComponent(owner)
	, m_Health(startHP)
{
}

void QbertHealthComponent::Death()
{
	--m_Health;
	Notify(Event::PlayerDeath);
}
