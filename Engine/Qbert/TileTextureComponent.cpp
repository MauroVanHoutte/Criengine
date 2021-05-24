#include "TileTextureComponent.h"
#include <SDL.h>
#include <Renderer.h>
#include <ResourceManager.h>

TileTextureComponent::TileTextureComponent(cri::GameObject* pOwner)
	: TextureComponent(pOwner)
	, m_TimesJumpedOn{0}
{
	SetTexture(cri::ResourceManager::GetInstance().LoadTexture("QbertTileTextures.png"));
	m_Difficulty = 1;
}

void TileTextureComponent::SetDifficulty(int difficulty)
{
	m_Difficulty = difficulty;
}

void TileTextureComponent::JumpedOn()
{
	++m_TimesJumpedOn;
}

void TileTextureComponent::Render() const
{
	SDL_Rect srcRect;
	SDL_QueryTexture(GetTexture()->GetSDLTexture(), nullptr, nullptr, &srcRect.w, &srcRect.h);
	srcRect.w /= 2;
	srcRect.h /= 3;
	int col = 0;
	srcRect.x = col * srcRect.w;
	auto center = m_RelativeTransform.GetPosition() + m_pOwner->m_Transform.GetPosition();
	int row = 0;
	switch (m_Difficulty)
	{
	case  1:
		if (m_TimesJumpedOn > 0)
		{
			row = 1;
		}
		srcRect.y = row * srcRect.h;
		
		cri::Renderer::GetInstance().RenderTexture(*GetTexture(), center.x - GetWidth(), center.y - GetHeight(), GetHeight(), GetWidth(), srcRect);
		break;

	case 2:
		if (m_TimesJumpedOn > 0)
		{
			++row;
		}
		if (m_TimesJumpedOn > 1)
		{
			++row;
		}
		srcRect.y = row * srcRect.h;

		cri::Renderer::GetInstance().RenderTexture(*GetTexture(), center.x - GetWidth(), center.y - GetHeight(), GetHeight(), GetWidth(), srcRect);
		break;

	case 3:
		row = m_TimesJumpedOn % 2;

		srcRect.y = row * srcRect.h;

		cri::Renderer::GetInstance().RenderTexture(*GetTexture(), center.x - GetWidth(), center.y - GetHeight(), GetHeight(), GetWidth(), srcRect);
		break;

	case 4:
		row = m_TimesJumpedOn % 3;

		srcRect.y = row * srcRect.h;

		cri::Renderer::GetInstance().RenderTexture(*GetTexture(), center.x - GetWidth(), center.y - GetHeight(), GetHeight(), GetWidth(), srcRect);
		break;
	}
}

bool TileTextureComponent::IsCorrect() const
{
	switch (m_Difficulty)
	{
	case  1:
		if (m_TimesJumpedOn > 0)
		{
			return true;
		}
		break;

	case 2:
		if (m_TimesJumpedOn > 1)
		{
			return true;
		}
		break;

	case 3:
		if (m_TimesJumpedOn % 2 == 1 )
		{
			return true;
		}
		break;
		
	case 4:
		if (m_TimesJumpedOn % 3 == 2)
		{
			return true;
		}
	}
    return false;
}
