#pragma once
#include "TextObject.h"

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
	};
}