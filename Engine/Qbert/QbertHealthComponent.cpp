#include "QbertHealthComponent.h"
#include "ServiceLocator.h"

QbertHealthComponent::QbertHealthComponent(cri::GameObject* owner, int startHP)
	: BaseComponent(owner)
	, m_Health(startHP)
{
}

void QbertHealthComponent::Death()
{
	--m_Health;
	Notify(Event::PlayerDeath);
	ServiceLocator::GetSoundSystem()->Play("../Data/sounds_door1.wav", 0, 100);
}
