#include "MiniginPCH.h"
#include "TextComponent.h"
#include "Renderer.h"
#include "TextRenderer.h"


TextComponent::TextComponent(dae::GameObject* owner, const std::string& text, const std::string& font, int fontSize, const glm::vec3& pos, const glm::vec3& color)
	: BaseComponent(owner)
	, m_Text{text}
	, m_Color{(Uint8)color.x, (Uint8)color.y, (Uint8)color.z}
	, m_Transform{}
	, m_Font{font}
	, m_FontSize{fontSize}
	, m_DoRender(true)
{
	m_Transform.SetPosition(pos.x, pos.y, pos.z);
}

TextComponent::~TextComponent()
{
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
	m_Text = text;
}

void TextComponent::SetColor(const glm::vec3& color)
{
	m_Color.r = (Uint8)color.x;
	m_Color.g = (Uint8)color.y;
	m_Color.b = (Uint8)color.z;
}

void TextComponent::SetFont(const std::string& font)
{
	m_Font = font;
}

void TextComponent::SetSize(int size)
{
	m_FontSize = size;
}

void TextComponent::Render() const
{
	if (m_DoRender)
	{
		TextRenderer::GetInstance()->RenderString(m_Text, { m_Transform.GetPosition().x, m_Transform.GetPosition().y, 0.f }, m_Font, m_FontSize, m_Color);
	}
}

void TextComponent::SwapDoRender()
{
	m_DoRender = !m_DoRender;
}
