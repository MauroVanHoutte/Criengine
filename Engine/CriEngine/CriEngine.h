#pragma once
#include "QbertGame.h"

struct SDL_Window;
namespace cri
{
	class CriEngine
	{
	public:
		void Initialize();
		void LoadGame() const;
		void Cleanup();
		void Run();
	private:
		SDL_Window* m_Window{};
		QbertGame m_QbertGame{};
	};
}