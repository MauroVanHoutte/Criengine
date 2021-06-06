#pragma once
#include <BaseComponent.h>
#include <glm/vec2.hpp>
#include "QbertJumperComponent.h"	

class DiskComponent : public BaseComponent
{
public:
	DiskComponent(cri::GameObject* owner, glm::vec2 target);

	void JumpedOn(cri::GameObject* qbert);

	void FixedUpdate() override;

	void Update() override;

private:
	glm::vec2 m_Target;
	bool m_JumpedOn;
	float m_Speed = 100.f;
	QbertJumperComponent* m_pQbertJumper = nullptr;

	float m_AnimationCounter = 0.f;
	float m_SecsPerFrame = 0.2f;

};