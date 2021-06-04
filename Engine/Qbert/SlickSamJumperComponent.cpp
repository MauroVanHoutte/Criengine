#include "SlickSamJumperComponent.h"
#include <Timer.h>
#include <random>
#include "SingleRowAnimationComponent.h"
#include "TileTextureComponent.h"

SlickSamJumperComponent::SlickSamJumperComponent(cri::GameObject* owner)
	: BaseJumperComponent(owner, 0.8f, "", "")
{
	SetTileOffset(0.f, -30.f);
}

void SlickSamJumperComponent::Update()
{
	if (!m_IsJumping)
	{
		m_PauseCounter += Timer::GetInstance()->GetElapsed();
		if (m_PauseCounter > m_PauseDuration)
		{
			if (std::rand() % 2 == 0)
				Jump(-1, 1);
			else
				Jump(1, 1);
			m_PauseCounter = 0.f;
		}
	}
}

void SlickSamJumperComponent::HandleAnimation(int colDir, int)
{
	auto AnimationComp = m_pOwner->GetComponent<SingleRowAnimationComponent>();
	assert(AnimationComp != nullptr);

	if (colDir < 0)
	{
		AnimationComp->SetAnimation(0);
	}
	if (colDir > 0)
	{
		AnimationComp->SetAnimation(1);
	}

	AnimationComp->NextFrame();
}

void SlickSamJumperComponent::HandleStartPos()
{
}

void SlickSamJumperComponent::JumpedOff()
{
	m_pOwner->Deactivate();
}

void SlickSamJumperComponent::JumpedOn()
{
	m_Target->GetComponent<TileTextureComponent>()->SlickSamJumpedOn();
}
