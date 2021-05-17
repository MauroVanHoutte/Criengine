#pragma once
#include "SoundSystem.h"

class ServiceLocator
{
public:
	static void RegisterSoundSystem(SoundSystem* system);
	static SoundSystem* GetSoundSystem();
	static void Destroy();
private:
	static SoundSystem* m_SoundSystem;
};
