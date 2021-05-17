#pragma once
#include <string>

class SoundSystem
{
public:
	virtual ~SoundSystem() = default;
	virtual void Play(const std::string& filename, int looping, int volume) = 0;
};