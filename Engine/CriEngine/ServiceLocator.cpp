#include "ServiceLocator.h"
#include "NullSoundSystem.h"

SoundSystem* ServiceLocator::m_SoundSystem = nullptr;

void ServiceLocator::RegisterSoundSystem(SoundSystem* system)
{
	if (m_SoundSystem != nullptr)
	{
		delete m_SoundSystem;
	}
	m_SoundSystem = system;
}

SoundSystem* ServiceLocator::GetSoundSystem()
{
	if (m_SoundSystem == nullptr)
	{
		m_SoundSystem = new NullSoundSystem();
	}
	return m_SoundSystem;
}

void ServiceLocator::Destroy()
{
	if (m_SoundSystem != nullptr)
	{
		delete m_SoundSystem;
	}
}
