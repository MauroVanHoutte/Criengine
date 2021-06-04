#include "SingleRowAnimationComponent.h"
#include <SDL.h>
#include <Renderer.h>
#include <Timer.h>

SingleRowAnimationComponent::SingleRowAnimationComponent(cri::GameObject* owner, int nrAnimations, int framesPerAnim, std::shared_ptr<cri::Texture2D> sheet)
	: TextureComponent(owner)
	, m_NrAnimations{nrAnimations}
	, m_NrFramesPerAnim{framesPerAnim}
	, m_CurrentAnimation{0}
	, m_CurrentFrame{0}
{
	SetTexture(sheet);
}

void SingleRowAnimationComponent::Render() const
{
	SDL_Rect srcRect;
	int fullWidth;
	SDL_QueryTexture(GetTexture()->GetSDLTexture(), nullptr, nullptr, &fullWidth, &srcRect.h );
	srcRect.w = fullWidth / (m_NrAnimations * m_NrFramesPerAnim);
	srcRect.y = 0;
	srcRect.x = (m_CurrentAnimation * m_NrFramesPerAnim + m_CurrentFrame) * srcRect.w;
	auto center = m_RelativeTransform.GetPosition() + m_pOwner->m_Transform.GetPosition();
	cri::Renderer::GetInstance().RenderTexture(*GetTexture(), center.x - GetWidth() / 2.f, center.y - GetHeight() / 2.f, GetWidth(), GetHeight(), srcRect);
}

void SingleRowAnimationComponent::NextFrame()
{
	++m_CurrentFrame;
	if (m_CurrentFrame >= m_NrFramesPerAnim)
	{
		m_CurrentFrame = 0;
	}
}

void SingleRowAnimationComponent::SetFrame(int frame)
{
	assert(frame < m_NrFramesPerAnim);
	m_CurrentFrame = frame;
}

void SingleRowAnimationComponent::SetAnimation(int nrAnimation)
{
	assert(nrAnimation < m_NrAnimations);
	m_CurrentAnimation = nrAnimation;
}
