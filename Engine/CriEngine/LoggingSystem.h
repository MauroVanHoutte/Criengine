#pragma once
#include "SoundSystem.h"
#include <iostream>

class LoggingSystem : public SoundSystem
{
public:
	virtual void Play(const std::string& filename, int looping, int volume) override
	{
		std::cout << "Play " << filename << "at volume " << volume << std::endl;
		looping;
	};
};