#pragma once
#include <BaseComponent.h>
#include <vector>
#include <glm/vec2.hpp>
#include <Subject.h>

enum class Type 
{
	Enemy,
	SlickSam,
	GreenBall,
	Qbert
};

class BaseColliderComponent : public BaseComponent, public Subject
{
public:
	BaseColliderComponent(cri::GameObject* owner, float width, float height, Type type);
	~BaseColliderComponent();

	void Render() const override;

	void LateUpdate() override;

	void QbertCheckOverlap();

	bool IsOverlapping(BaseColliderComponent* other);

protected:
	static std::vector<BaseColliderComponent*> m_Colliders;
	glm::vec2 m_Size;
	Type m_Type;
};