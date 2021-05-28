#pragma once
#include <BaseComponent.h>
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)
#include <memory>
#include <Subject.h>


class Level;
class JumperComponent : public BaseComponent, public Subject
{
public:
	JumperComponent(cri::GameObject* pOwner, float jumpDuration, const std::string& jumpSoundName, const std::string& fallSoundName);
	JumperComponent() = delete;

	void Update() override;

	void Jump(int colDir, int rowDir);

	void SetStartPos(Level* pLevel, int startRow, int startCol);


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

	int m_LivesLeft;

	std::string m_JumpSoundName;
	std::string m_FallSoundName;

};
