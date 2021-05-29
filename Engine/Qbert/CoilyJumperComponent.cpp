#include "CoilyJumperComponent.h"
#include "SingleRowAnimationComponent.h"

CoilyJumperComponent::CoilyJumperComponent(cri::GameObject* owner)
	: BaseJumperComponent(owner, 0.8f, "jumpCoily.wav", "")
{
}

void CoilyJumperComponent::HandleAnimation(int colDir, int rowDir)
{
	auto AnimationComp = m_pOwner->GetComponent<SingleRowAnimationComponent>();

	if (colDir < 0 && rowDir > 0)
	{
		AnimationComp->SetAnimation(3);
	}

	if (colDir > 0 && rowDir < 0)
	{
		AnimationComp->SetAnimation(0);
	}

	if (colDir < 0 && rowDir < 0)
	{
		AnimationComp->SetAnimation(1);
	}

	if (colDir > 0 && rowDir > 0)
	{
		AnimationComp->SetAnimation(2);
	}

	AnimationComp->NextFrame();
}

void CoilyJumperComponent::JumpedOff()
{
	SetStartPos(m_pLevel, 0, 0);
}

void CoilyJumperComponent::HandleStartPos(std::shared_ptr<cri::GameObject> target)
{
	float yOffset = -30.f;
	m_pOwner->m_Transform.SetPosition(target->m_Transform.GetPosition().x, target->m_Transform.GetPosition().y + yOffset, 0);
	m_pOwner->GetComponent<SingleRowAnimationComponent>()->SetAnimation(2);
}
