#include "MiniginPCH.h"
#include "TextComponent.h"
#include <SDL.h>
#include <SDL_ttf.h>

#include "TextObject.h"
#include "Renderer.h"


TextComponent::TextComponent(dae::GameObject* owner, const std::string& text, const std::string& font, int fontSize, const glm::vec3& pos)
	: BaseComponent(owner)
	, m_Transform{}
	, m_pFont{nullptr}
	, m_pTexture{nullptr}
{
	m_Transform.SetPosition(pos.x, pos.y, pos.z);
	m_pFont = new dae::Font("../Data/" + font, fontSize);
	const SDL_Color color = { 255,255,255 }; // only white text is supported now
	const auto surf = TTF_RenderText_Blended(m_pFont->GetFont(), text.c_str(), color);
	m_pTexture = new dae::Texture2D(SDL_CreateTextureFromSurface(dae::Renderer::GetInstance().GetSDLRenderer(), surf));
	SDL_FreeSurface(surf);
}

TextComponent::~TextComponent()
{
	delete m_pTexture;
	delete m_pFont;
}

void TextComponent::SetPosition(const glm::vec3& pos)
{
	m_Transform.SetPosition(pos.x, pos.y, pos.z);
}

const glm::vec3& TextComponent::GetPosition() const
{
	return m_Transform.GetPosition();
}

void TextComponent::SetText(const std::string& text)
{
	delete m_pTexture;
	m_pTexture = nullptr;
	const SDL_Color color = { 255,255,255 }; // only white text is supported now
	const auto surf = TTF_RenderText_Blended(m_pFont->GetFont(), text.c_str(), color);
	m_pTexture = new dae::Texture2D(SDL_CreateTextureFromSurface(dae::Renderer::GetInstance().GetSDLRenderer(), surf));
	SDL_FreeSurface(surf);
}

void TextComponent::Render() const
{
	if (m_pTexture != nullptr)
	{
		const auto pos = m_Transform.GetPosition();
		dae::Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y);
	}
}
