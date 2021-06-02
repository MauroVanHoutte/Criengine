#pragma once
#include <BaseComponent.h>
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)
#include <memory>
#include <Subject.h>


class Level;
class BaseJumperComponent : public BaseComponent, public Subject
{
public:
	BaseJumperComponent(cri::GameObject* pOwner, float jumpDuration, const std::string& jumpSoundName, const std::string& fallSoundName);
	BaseJumperComponent() = delete;

	void FixedUpdate() override;

	void Jump(int colDir, int rowDir);

	void SetStartPos(Level* pLevel, int startRow, int startCol);

	virtual void JumpedOff() {};

	virtual void HandleAnimation(int , int ) {};

	virtual void HandleStartPos(std::shared_ptr<cri::GameObject> target) {};

	virtual void JumpedOn() {};


protected:
	Level* m_pLevel;
	std::shared_ptr<cri::GameObject> m_Target;

private:
	
	void JumpOffMap(int colDir, int rowDir);
	glm::ivec2 m_Pos;
	glm::vec2 m_JumpStartPos;
	float m_JumpDuration;
	float m_JumpDurationOffMap;
	float m_JumpDurationTile;
	float m_JumpCounter;
	bool m_IsJumping;
	glm::vec2 m_InitialJumpVelocity;
	float m_Gravity;

	std::string m_JumpSoundName;
	std::string m_FallSoundName;
};
