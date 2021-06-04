#include "BaseColliderComponent.h"
#include <SDL.h>
#include <Renderer.h>
#include "BaseColliderComponent.h"
#include "QbertJumperComponent.h"

std::vector<BaseColliderComponent*> BaseColliderComponent::m_Colliders{};

BaseColliderComponent::BaseColliderComponent(cri::GameObject* owner, float width, float height, Type type)
	: BaseComponent(owner)
	, m_Size{width, height}
	, m_Type{type}
{
	m_Colliders.push_back(this);
}

BaseColliderComponent::~BaseColliderComponent()
{
	m_Colliders.erase(std::remove(m_Colliders.begin(), m_Colliders.end(), this), m_Colliders.end());
}

void BaseColliderComponent::Render() const
{
	SDL_Rect dstRect;
	dstRect.w = int(m_Size.x);
	dstRect.h = int(m_Size.y);
	dstRect.x = int(m_pOwner->m_Transform.GetPosition().x - dstRect.w * 0.5f);
	dstRect.y = int(m_pOwner->m_Transform.GetPosition().y - dstRect.h * 0.5f);
	SDL_RenderDrawRect(cri::Renderer::GetInstance().GetSDLRenderer(), &dstRect);
}

void BaseColliderComponent::LateUpdate()
{
	switch (m_Type)
	{
	case Type::Enemy:
		break;
	case Type::SlickSam:
		break;
	case Type::GreenBall:
		break;
	case Type::Qbert:
		QbertCheckOverlap();
		break;
	default:
		break;
	}
}

void BaseColliderComponent::QbertCheckOverlap()
{
	for (size_t i = 0; i < m_Colliders.size(); i++)
	{
		if (!m_Colliders[i]->m_IsActive || !m_Colliders[i]->m_pOwner->IsActive())
		{
			continue;
		}
		if (IsOverlapping(m_Colliders[i]))
		{
			switch (m_Colliders[i]->m_Type)
			{
			case Type::SlickSam:
				m_Colliders[i]->m_pOwner->Deactivate();
				break;
			case Type::Enemy:
				m_pOwner->GetComponent<QbertJumperComponent>()->JumpedOff(); //coily bug 
				break;
			case Type::GreenBall:
				break;
			default:
				break;
			}
		}
	}
}

bool BaseColliderComponent::IsOverlapping(BaseColliderComponent* other)
{
	auto position = m_pOwner->m_Transform.GetPosition();
	auto otherPos = other->m_pOwner->m_Transform.GetPosition();
	bool x = abs(position.x - otherPos.x) <= (m_Size.x + other->m_Size.x) * 0.5f;
	bool y = abs(position.y - otherPos.y) <= (m_Size.y + other->m_Size.y) * 0.5f;

	return x && y;
}
