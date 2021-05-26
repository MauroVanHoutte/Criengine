#pragma once
#include <BaseComponent.h>
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)
#include <memory>


class Level;
class JumperComponent : public BaseComponent
{
public:
	JumperComponent(cri::GameObject* pOwner, Level* pLevel, int starRow, int startCol);
	JumperComponent() = delete;

	void Update() override;

	void Jump(int colDir, int rowDir);


private:

	void JumpOffMap(int colDir, int rowDir);
	Level* m_pLevel;
	glm::ivec2 m_Pos;
	glm::vec2 m_JumpStartPos;
	std::shared_ptr<cri::GameObject> m_Target;
	float m_JumpDuration;
	float m_JumpDurationOffMap;
	float m_JumpDurationTile;
	float m_JumpCounter;
	bool m_IsJumping;
	glm::vec2 m_InitialJumpVelocity;
	float m_Gravity;

};
