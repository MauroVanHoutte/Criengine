#pragma once
#include "BaseJumperComponent.h"

#include "JumpCommand.h"

class CoilyJumperComponent : public BaseJumperComponent
{
public:
	CoilyJumperComponent(cri::GameObject* owner, std::shared_ptr<cri::GameObject> qbert1, std::shared_ptr<cri::GameObject> qbert2);
	CoilyJumperComponent() = delete;


	void Update() override;


	void HandleAnimation(int colDir, int rowDir) override;

	void JumpedOff() override;
	void OnJumpingOff() override;

	void HandleStartPos() override;

	void SetIsPlayerControlled(bool isPlayerControlled);
	void SetIsEgg(bool isEgg);

	void ConnectJumpCommands();
	void DisconnectJumpCommands();

	//AI
	
	void JumpToClosestQbert();

private:
	bool m_IsEgg{ true };
	bool m_IsPlayerControlled{ false };
	float m_JumpInterval = 0.2f;
	float m_JumpCounter = 0.f;

	std::shared_ptr<JumpCommand> m_JumpUpLeft;
	std::shared_ptr<JumpCommand> m_JumpUpRight;
	std::shared_ptr<JumpCommand> m_JumpDownRight;
	std::shared_ptr<JumpCommand> m_JumpDownLeft;

	std::shared_ptr<cri::GameObject> m_Qbert1;
	std::shared_ptr<cri::GameObject> m_Qbert2;
};