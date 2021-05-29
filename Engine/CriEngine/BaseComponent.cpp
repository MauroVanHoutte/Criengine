#include "BaseComponent.h"

BaseComponent::BaseComponent(cri::GameObject* owner)
	: m_pOwner{ owner }
{
}

bool BaseComponent::IsActive()
{
	return m_IsActive;
}

void BaseComponent::SetIsActive(bool isActive)
{
	m_IsActive = isActive;
}

