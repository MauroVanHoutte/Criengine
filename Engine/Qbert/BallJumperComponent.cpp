#include "BallJumperComponent.h"
#include "SingleRowAnimationComponent.h"
#include <Timer.h>

BallJumperComponent::BallJumperComponent(cri::GameObject* pOwner)
	: BaseJumperComponent(pOwner, 1.f, "jumpBall.wav", "", false)
{
	SetTileOffset(0.f, -30.f);
}

void BallJumperComponent::Update()
{
	if (!m_IsJumping)
	{
		m_PauseCounter += Timer::GetInstance()->GetElapsed();
		if (m_PauseCounter > m_PauseDuration)
		{
			if (std::rand() % 2 == 0)
				Jump(1, 1);
			else
				Jump(-1, 1);

			m_PauseCounter -= m_PauseDuration;
		}
	}
}

void BallJumperComponent::Spawn(cri::GameObject* target)
{
	target = nullptr; //todo
}

void BallJumperComponent::HandleAnimation(int , int)
{
	auto AnimationComp = m_pOwner->GetComponent<SingleRowAnimationComponent>();
	AnimationComp->NextFrame();
}

void BallJumperComponent::JumpedOff()
{
	m_pOwner->Deactivate();
}
