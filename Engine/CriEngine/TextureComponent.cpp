#include "TextureComponent.h"
#include "Renderer.h"
#include <assert.h>

TextureComponent::TextureComponent(cri::GameObject* pOwner)
	: BaseComponent(pOwner)
	, m_Height{50.f}
	, m_Width{50.f}
	, m_DoRender{true}
{
	m_RelativeTransform.SetPosition(0, 0);
}

void TextureComponent::SetTexture(std::shared_ptr<cri::Texture2D> texture)
{
	assert(texture != nullptr);
	m_Texture = texture;
}

std::shared_ptr<cri::Texture2D> TextureComponent::GetTexture() const
{
	return m_Texture;
}

void TextureComponent::Render() const
{
	auto center = m_RelativeTransform.GetPosition() + m_pOwner->m_Transform.GetPosition();
	cri::Renderer::GetInstance().RenderTexture(*m_Texture, center.x - m_Width/2.f, center.y - m_Height/2.f, m_Height, m_Width);
}

void TextureComponent::SetHeight(float height)
{
	m_Height = height;
}

float TextureComponent::GetHeight() const
{
	return m_Height;
}

void TextureComponent::SetWidth(float width)
{
	m_Width = width;
}

float TextureComponent::GetWidth() const
{
	return m_Width;
}

void TextureComponent::SetDoRender(bool doRender)
{
	m_DoRender = doRender;
}

bool TextureComponent::GetDoRender()
{
	return m_DoRender;
}
