#include "BallJumperComponent.h"
#include "SingleRowAnimationComponent.h"

BallJumperComponent::BallJumperComponent(cri::GameObject* pOwner)
	: BaseJumperComponent(pOwner, 1.f, "", "")
{
}

void BallJumperComponent::Spawn(cri::GameObject* target)
{
	target = nullptr; //todo
}

void BallJumperComponent::HandleAnimation(int , int)
{
	auto AnimationComp = m_pOwner->GetComponent<SingleRowAnimationComponent>();
	assert(AnimationComp != nullptr);
	AnimationComp->NextFrame();
}
