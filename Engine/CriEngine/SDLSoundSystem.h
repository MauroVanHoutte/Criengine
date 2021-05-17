#pragma once
#include "SoundSystem.h"
#include <map>
#include <queue>
#include <mutex>
#include <future>

#pragma warning(disable:4244)
#include "audio.h"
#pragma warning(default:4244)

struct AudioRequest
{
	std::string filename;
	int looping;
	int volume;
};

class SDLSoundSystem final : public SoundSystem
{
public:
	SDLSoundSystem();
	~SDLSoundSystem();
	void Play(const std::string& filename, int looping, int volume) override;
	

private:
	void QueueLoop();

	bool m_Running = true;
	std::mutex m_Mutex;
	std::map<std::string, Audio*> m_AudioMap;
	std::queue<AudioRequest> m_AudioQueue;
	std::future<void> m_Thread;
};