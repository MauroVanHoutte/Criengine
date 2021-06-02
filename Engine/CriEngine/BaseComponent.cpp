#include "BaseComponent.h"

BaseComponent::BaseComponent(cri::GameObject* owner)
	: m_pOwner{ owner }
{
	m_pOwner->AddComponent(this);
}

bool BaseComponent::IsActive()
{
	return m_IsActive;
}

void BaseComponent::SetIsActive(bool isActive)
{
	m_IsActive = isActive;
}

bool BaseComponent::IsOwnerActive()
{
	return m_pOwner->IsActive();
}

