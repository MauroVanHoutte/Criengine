#pragma once
#include <BaseComponent.h>
#include <glm/vec2.hpp>
#include <memory>

class Level;
class BaseJumperComponent : public BaseComponent
{
public:
	BaseJumperComponent(cri::GameObject* pOwner, float jumpDuration, const std::string& jumpSoundName, const std::string& fallSoundName);
	BaseJumperComponent() = delete;

	void Update() override;

	void Jump(int colDir, int rowDir);

	void SetStartPos(Level* pLevel, int startRow, int startCol);

	virtual void JumpedOff() {};

	virtual void HandleAnimation(int colDir, int rowDir) {};

	virtual void HandleStartPos(std::shared_ptr<cri::GameObject> target) {};

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

	std::string m_JumpSoundName;
	std::string m_FallSoundName;
};
