#include "SDLSoundSystem.h"
#pragma warning(disable:4244)
#include "audio.c"
#pragma warning(default:4244)
#include <iostream>


SDLSoundSystem::SDLSoundSystem()
{
	_putenv("SDL_AUDIODRIVER=DirectSound");
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}
	initAudio();
	m_Thread = std::async(std::launch::async, [this]() { QueueLoop(); });
}

SDLSoundSystem::~SDLSoundSystem()
{
	m_Running = false;
	m_Thread.get();
	for (auto it = m_AudioMap.begin(); it != m_AudioMap.end(); it++)
	{
		freeAudio(it->second);
	}
	endAudio();
}

void SDLSoundSystem::Play(const std::string& filename, int looping, int volume)
{
	AudioRequest request{ filename, looping, volume };
	std::unique_lock<std::mutex> lock{ m_Mutex };
	m_AudioQueue.push(request);
	lock.unlock();
}

void SDLSoundSystem::QueueLoop()
{
	while(m_Running)
	{
		if (m_AudioQueue.size() > 0)
		{
			std::unique_lock<std::mutex> lock{m_Mutex};
			auto request = m_AudioQueue.front();
			m_AudioQueue.pop();
			lock.unlock();
			if (m_AudioMap.find(request.filename) == m_AudioMap.end())
			{
			 	auto sound = createAudio(("../Data/" + request.filename).c_str(), uint8_t(request.looping), SDL_MIX_MAXVOLUME);
				m_AudioMap[request.filename] = sound;
			}
			if (request.looping == 0)
			{
				playSoundFromMemory(m_AudioMap[request.filename], request.volume);
			}
			else
			{
				playMusicFromMemory(m_AudioMap[request.filename], request.volume);
			}
			
			std::cout << "playing : " << request.filename << std::endl;
		}
	}
}
