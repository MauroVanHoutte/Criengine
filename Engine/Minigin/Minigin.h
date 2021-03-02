#pragma once
#include "TextObject.h"
#include "QbertGame.h"

struct SDL_Window;
namespace dae
{
	class Minigin
	{
	public:
		void Initialize();
		void LoadGame() const;
		void Cleanup();
		void Run();
	private:
		SDL_Window* m_Window{};
		std::shared_ptr<TextObject> m_FpsCounter;
		QbertGame m_QbertGame{};
	};
}