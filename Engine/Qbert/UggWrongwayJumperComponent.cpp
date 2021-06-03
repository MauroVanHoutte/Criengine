#include "UggWrongwayJumperComponent.h"
#include <Timer.h>
#include "SingleRowAnimationComponent.h"

UggWrongwayJumperComponent::UggWrongwayJumperComponent(cri::GameObject* owner)
	: BaseJumperComponent(owner, 0.9f, "", "")
{
}

void UggWrongwayJumperComponent::Update()
{
	if (!m_IsJumping)
	{
		m_PauseCounter += Timer::GetInstance()->GetElapsed();
		if (m_PauseCounter > m_PauseDuration)
		{
			if (std::rand() % 2 == 0)
			{
				if (m_GoingRight)
					Jump(1, -1);
				else
					Jump(-1, -1);
			}
			else
			{
				if (m_GoingRight)
					Jump(1, 0);
				else
					Jump(-1, 0);
			}
			m_PauseCounter = 0.f;
		}
	}
}

void UggWrongwayJumperComponent::HandleStartPos()
{
}

void UggWrongwayJumperComponent::JumpedOff()
{
	m_pOwner->Deactivate();
}

void UggWrongwayJumperComponent::HandleAnimation(int colDir, int )
{
	auto AnimationComp = m_pOwner->GetComponent<SingleRowAnimationComponent>();
	if (colDir > 0)
	{
		AnimationComp->SetAnimation(0);
	}
	if (colDir < 0)
	{
		AnimationComp->SetAnimation(1);
	}

	AnimationComp->NextFrame();
}

void UggWrongwayJumperComponent::SetGoingRight(bool goingRight)
{
	m_GoingRight = goingRight;
	if (goingRight)
		SetTileOffset(-30.f, 20.f);
	else
		SetTileOffset(30.f, 20.f);

}

bool UggWrongwayJumperComponent::GetGoingRight()
{
	return m_GoingRight;
}
