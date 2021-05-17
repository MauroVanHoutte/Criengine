#include "Texture2D.h"
#include <SDL.h>

cri::Texture2D::~Texture2D()
{
	SDL_DestroyTexture(m_Texture);
}

//dae::Texture2D& dae::Texture2D::operator=(const Texture2D&& other) noexcept
//{
//	if (m_Texture != nullptr)
//	{
//		 SDL_DestroyTexture(m_Texture);
//	}
//	m_Texture = other.m_Texture;
//	return *this;
//}

SDL_Texture* cri::Texture2D::GetSDLTexture() const
{
	return m_Texture;
}

cri::Texture2D::Texture2D(SDL_Texture* texture)
{
	m_Texture = texture;
}

//dae::Texture2D::Texture2D()
//	: m_Texture{nullptr}
//{
//}
