#include "QbertJumperComponent.h"
#include "SingleRowAnimationComponent.h"
#include "TileTextureComponent.h"

QbertJumperComponent::QbertJumperComponent(cri::GameObject* pOwner)
	: BaseJumperComponent(pOwner, 0.7f, "jumpQbert.wav", "fallQbert.wav")
{
}

void QbertJumperComponent::JumpedOff()
{
	SetStartPos(m_pLevel, 0, 0);
	Notify(Event::QbertDeath);
}

void QbertJumperComponent::HandleAnimation(int colDir, int rowDir)
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

void QbertJumperComponent::HandleStartPos(std::shared_ptr<cri::GameObject> target)
{
	float yOffset = -30.f;
	m_pOwner->m_Transform.SetPosition(target->m_Transform.GetPosition().x, target->m_Transform.GetPosition().y + yOffset, 0);
	m_pOwner->GetComponent<SingleRowAnimationComponent>()->SetAnimation(2);
}

void QbertJumperComponent::JumpedOn()
{
	m_Target->GetComponent<TileTextureComponent>()->JumpedOn();
}
