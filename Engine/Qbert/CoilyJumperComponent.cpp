#include "CoilyJumperComponent.h"
#include "SingleRowAnimationComponent.h"

CoilyJumperComponent::CoilyJumperComponent(cri::GameObject* owner)
	: BaseJumperComponent(owner, 0.8f, "jumpCoily.wav", "")
{
	SetTileOffset(0.f, -30.f);
}

void CoilyJumperComponent::HandleAnimation(int colDir, int rowDir)
{
	auto AnimationComp = m_pOwner->GetComponent<SingleRowAnimationComponent>();
	assert(AnimationComp != nullptr);

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

void CoilyJumperComponent::HandleStartPos()
{
	m_pOwner->GetComponent<SingleRowAnimationComponent>()->SetAnimation(2);
}
