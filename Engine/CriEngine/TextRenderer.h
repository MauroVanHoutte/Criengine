#pragma once
#include "Texture2D.h"
#include <unordered_map>
#include <vector>
#include <SDL.h>
#include <SDL_ttf.h>

#pragma warning(push)
#pragma warning(disable : 4201)
#include <glm/vec3.hpp>
#pragma warning(pop)

struct FontID
{
	std::string Name;
	unsigned int Size;
	SDL_Color Color;
	unsigned int ID;

	bool operator==(const FontID& other) const;
};

namespace std
{
	template<>
	struct hash<FontID>
	{
		std::size_t operator()(const FontID& font) const
		{
			return font.ID;
		}
	};
}

class TextRenderer
{
public:
	static TextRenderer* GetInstance();

	void AddFont(const std::string& font, unsigned int size, const SDL_Color& color);
	void RenderString(const std::string& text, const glm::vec3& location, const std::string& fontName, unsigned int size, const SDL_Color& color) const;

	void Cleanup();

private:
	TextRenderer() = default;
	TextRenderer(TextRenderer&) = delete;
	TextRenderer(TextRenderer&&) = delete;
	TextRenderer& operator=(TextRenderer&) = delete;
	TextRenderer& operator=(TextRenderer&&) = delete;


	static TextRenderer* m_pInstance;

	unsigned int m_NrFonts{0};

	std::vector<FontID> m_FontIDs;
	std::unordered_map<FontID, std::unordered_map<char, cri::Texture2D*>> m_Fonts;
};