#pragma once
#include "SoundSystem.h"
#include <string>

class NullSoundSystem final : public SoundSystem
{
public:
	void Play(const std::string& filename, int looping, int volume) override { filename; volume; looping; };
};