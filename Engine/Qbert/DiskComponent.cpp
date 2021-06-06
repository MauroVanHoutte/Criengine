#include "DiskComponent.h"
#pragma warning(push)
#pragma warning(disable:4201)
#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>
#pragma warning(pop)
#include <Timer.h>
#include "SingleRowAnimationComponent.h"

DiskComponent::DiskComponent(cri::GameObject* owner, glm::vec2 target)
	:BaseComponent(owner)
	, m_Target{target}
{
}

void DiskComponent::JumpedOn(cri::GameObject* qbert)
{
	m_pQbertJumper = qbert->GetComponent<QbertJumperComponent>();
	m_pQbertJumper->SetIsOnDisk(true);
	m_JumpedOn = true;
}

void DiskComponent::FixedUpdate()
{
	if (m_JumpedOn)
	{
		glm::vec2 currentPos = m_pOwner->m_Transform.GetPosition();
		glm::vec2 direction = m_Target - currentPos;
		direction = glm::normalize(direction);

		glm::vec2 newPos = currentPos + direction * m_Speed * Timer::GetInstance()->GetStepTime();

		m_pOwner->m_Transform.SetPosition(newPos.x, newPos.y);

		if (glm::distance2(newPos, m_Target) < 100.f)
		{
			m_pOwner->Deactivate();
			m_pQbertJumper->SetIsOnDisk(false);
			m_pQbertJumper->SetPos(0, -1);
			m_pQbertJumper->Jump(-1, 1);
		}
	}
}

void DiskComponent::Update()
{
	m_AnimationCounter += Timer::GetInstance()->GetElapsed();
	if (m_AnimationCounter > m_SecsPerFrame)
	{
		m_pOwner->GetComponent<SingleRowAnimationComponent>()->NextFrame();
		m_AnimationCounter -= m_SecsPerFrame;
	}
}
