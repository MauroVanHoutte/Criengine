#include "QbertJumperComponent.h"
#include "SingleRowAnimationComponent.h"
#include "TileTextureComponent.h"
#include "SceneManager.h"
#include "Scene.h"

QbertJumperComponent::QbertJumperComponent(cri::GameObject* pOwner)
	: BaseJumperComponent(pOwner, 0.7f, "jumpQbert.wav", "fallQbert.wav")
{
	SetTileOffset(0.f, -30.f);
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

void QbertJumperComponent::HandleStartPos()
{
	m_pOwner->GetComponent<SingleRowAnimationComponent>()->SetAnimation(2);
}

void QbertJumperComponent::JumpedOn()
{
	m_Target->GetComponent<TileTextureComponent>()->JumpedOn();
}
