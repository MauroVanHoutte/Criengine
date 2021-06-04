#pragma once
struct SDL_Window;
namespace cri
{
	class CriEngine
	{
	public:
		void Initialize();
		void Cleanup();
		void Run();
	private:
		SDL_Window* m_Window{};
	};
}