#include "TextRenderer.h"
#include "Font.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include "Renderer.h"
#include <algorithm>
#include <stdexcept>

TextRenderer* TextRenderer::m_pInstance = nullptr;

TextRenderer* TextRenderer::GetInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new TextRenderer();
	}
    return m_pInstance;
}

void TextRenderer::AddFont(const std::string& fontName, unsigned int size, const SDL_Color& color)
{
	FontID fontId{ fontName, size, color, m_NrFonts };

	if (std::find(m_FontIDs.begin(), m_FontIDs.end(), fontId) != m_FontIDs.end())
	{
		return;
	}

	m_FontIDs.push_back(fontId);
	++m_NrFonts;

	cri::Font font{ "../Data/" + fontName, size };

	std::string temp;

	for (char i = 0; i < 127; i++)
	{
		temp = i;
		const auto surf = TTF_RenderText_Blended(font.GetFont(), temp.c_str(), color);
		m_Fonts[fontId][i] = new cri::Texture2D(SDL_CreateTextureFromSurface(cri::Renderer::GetInstance().GetSDLRenderer(), surf));
		SDL_FreeSurface(surf);
	}

}

void TextRenderer::RenderString(const std::string& text, const glm::vec3& location, const std::string& fontName, unsigned int size, const SDL_Color& color) const
{
	FontID fontId{ fontName, size, color, m_NrFonts };

	auto it = std::find(m_FontIDs.begin(), m_FontIDs.end(), fontId);
	if (it == m_FontIDs.end())
	{
		throw std::runtime_error("Font not found, add fonts using AddFont");
	}
	else
		fontId.ID = it->ID;

	float xOffset{ 0.f };
	float yOffset{ 0.f };

	int letterHeight{};
	int letterWidth{};
	SDL_QueryTexture(m_Fonts.find(fontId)->second.find('A')->second->GetSDLTexture(), nullptr, nullptr, &letterWidth, &letterHeight); //ONLY monospace fonts

	for (const char& c : text)
	{
		if (c == '\n')
		{
			yOffset += letterHeight;
			xOffset = 0;
			continue;
		}
		cri::Renderer::GetInstance().RenderTexture(*m_Fonts.find(fontId)->second.find(c)->second, location.x + xOffset, location.y + yOffset);
		xOffset += letterWidth;
	}
}

void TextRenderer::Cleanup()
{
	for (auto it = m_Fonts.begin(); it != m_Fonts.end(); it++)
	{
		for (auto texIt = it->second.begin(); texIt != it->second.end() ; texIt++)
		{
			delete texIt->second;
			texIt->second = nullptr;
		}
	}
	delete m_pInstance;
}

bool FontID::operator==(const FontID& other) const
{
	if (Color.r != other.Color.r)
	{
		return false;
	}
	if (Color.g != other.Color.g)
	{
		return false;
	}
	if (Color.b != other.Color.b)
	{
		return false;
	}
	return (other.Size == Size && Name.compare(other.Name) == 0);
}
