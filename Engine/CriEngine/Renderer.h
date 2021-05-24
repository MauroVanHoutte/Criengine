#pragma once
#include "Singleton.h"
#include "SDL.h"

struct SDL_Window;
struct SDL_Renderer;

namespace cri
{
	class Texture2D;
	/**
	 * Simple RAII wrapper for the SDL renderer
	 */
	class Renderer final : public Singleton<Renderer>
	{
	public:
		void Init(SDL_Window* window);
		void Render() const;
		void Destroy();
		SDL_Window* GetWindow() const;

		void RenderTexture(const Texture2D& texture, float x, float y) const;
		void RenderTexture(const Texture2D& texture, float x, float y, float width, float height) const;
		void RenderTexture(const Texture2D& texture, float x, float y, float width, float height, const SDL_Rect& sourceRect) const;


		SDL_Renderer* GetSDLRenderer() const { return m_Renderer; }
	private:
		SDL_Renderer* m_Renderer{};
		SDL_Window* m_Window{};
	};
}

