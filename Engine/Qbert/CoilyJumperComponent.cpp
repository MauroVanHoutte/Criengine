#include "CoilyJumperComponent.h"
#include "SingleRowAnimationComponent.h"
#include <InputManager.h>
#include <SceneManager.h>
#include <Timer.h>
#include "QbertJumperComponent.h"
#include "Level.h"


template <typename T> int sgn(T val) { //https://stackoverflow.com/questions/1903954/is-there-a-standard-sign-function-signum-sgn-in-c-c
	return (T(0) < val) - (val < T(0));
}


CoilyJumperComponent::CoilyJumperComponent(cri::GameObject* owner, std::shared_ptr<cri::GameObject> qbert1, std::shared_ptr<cri::GameObject> qbert2)
	: BaseJumperComponent(owner, 0.8f, "jumpCoily.wav", "")
	, m_Qbert1{qbert1}
	, m_Qbert2{qbert2}
{
	SetTileOffset(0.f, -30.f);
	m_JumpUpLeft = std::make_shared<JumpCommand>(-1, -1);
	cri::InputManager::GetInstance().AddKeyboardCommand(cri::SceneManager::GetInstance().GetCurrentSceneIdx(), cri::ButtonState::OnPressed, SDL_SCANCODE_Q, m_JumpUpLeft);
	cri::InputManager::GetInstance().AddControllerJoystickCommand(1, cri::SceneManager::GetInstance().GetCurrentSceneIdx(), 10000, cri::Joystick::Left, cri::JoystickDirection::UpLeft, m_JumpUpLeft);
	m_JumpUpRight = std::make_shared<JumpCommand>(1, -1);
	cri::InputManager::GetInstance().AddKeyboardCommand(cri::SceneManager::GetInstance().GetCurrentSceneIdx(), cri::ButtonState::OnPressed, SDL_SCANCODE_E, m_JumpUpRight);
	cri::InputManager::GetInstance().AddControllerJoystickCommand(1, cri::SceneManager::GetInstance().GetCurrentSceneIdx(), 10000, cri::Joystick::Left, cri::JoystickDirection::UpRight, m_JumpUpRight);
	m_JumpDownRight = std::make_shared<JumpCommand>(1, 1);
	cri::InputManager::GetInstance().AddKeyboardCommand(cri::SceneManager::GetInstance().GetCurrentSceneIdx(), cri::ButtonState::OnPressed, SDL_SCANCODE_D, m_JumpDownRight);
	cri::InputManager::GetInstance().AddControllerJoystickCommand(1, cri::SceneManager::GetInstance().GetCurrentSceneIdx(), 10000, cri::Joystick::Left, cri::JoystickDirection::DownRight, m_JumpDownRight);
	m_JumpDownLeft = std::make_shared<JumpCommand>(-1, 1);
	cri::InputManager::GetInstance().AddKeyboardCommand(cri::SceneManager::GetInstance().GetCurrentSceneIdx(), cri::ButtonState::OnPressed, SDL_SCANCODE_A, m_JumpDownLeft);
	cri::InputManager::GetInstance().AddControllerJoystickCommand(1, cri::SceneManager::GetInstance().GetCurrentSceneIdx(), 10000, cri::Joystick::Left, cri::JoystickDirection::DownLeft, m_JumpDownLeft);
}

void CoilyJumperComponent::Update()
{
	if (m_IsEgg && !m_IsJumping)
	{
		m_JumpCounter += Timer::GetInstance()->GetElapsed();
		if (m_JumpCounter > m_JumpInterval)
		{
			m_JumpCounter -= m_JumpInterval;
			if (std::rand() % 2 == 1)
				Jump(-1, 1);
			else
				Jump(1, 1);

		}
	}

	if (!m_IsPlayerControlled && !m_IsEgg && !m_IsJumping)
	{
		m_JumpCounter += Timer::GetInstance()->GetElapsed();
		if (m_JumpCounter > m_JumpInterval)
		{
			m_JumpCounter -= m_JumpInterval;
			JumpToClosestQbert();
		}
	}


}

void CoilyJumperComponent::HandleAnimation(int colDir, int rowDir)
{

	auto AnimationComps = m_pOwner->GetComponents<SingleRowAnimationComponent>();
	assert(AnimationComps.size() > 0);

	if (colDir < 0 && rowDir > 0)
	{
		AnimationComps[0]->SetAnimation(3);
	}

	if (colDir > 0 && rowDir < 0)
	{
		AnimationComps[0]->SetAnimation(0);
	}

	if (colDir < 0 && rowDir < 0)
	{
		AnimationComps[0]->SetAnimation(1);
	}

	if (colDir > 0 && rowDir > 0)
	{
		AnimationComps[0]->SetAnimation(2);
	}

	AnimationComps[0]->NextFrame();
	AnimationComps[1]->NextFrame();
}

void CoilyJumperComponent::JumpedOff()
{
	SetStartPos(m_pLevel, 0, 0);
}

void CoilyJumperComponent::OnJumpingOff()
{
	if (m_IsEgg)
	{
		m_IsJumping = false;
		SetIsEgg(false);
		if (m_IsPlayerControlled)
		{
			ConnectJumpCommands();
		}
	}
}

void CoilyJumperComponent::HandleStartPos()
{
	m_pOwner->GetComponent<SingleRowAnimationComponent>()->SetAnimation(2);
	SetIsEgg(true);
}

void CoilyJumperComponent::SetIsPlayerControlled(bool isPlayerControlled)
{
	m_IsPlayerControlled = isPlayerControlled;
}

void CoilyJumperComponent::SetIsEgg(bool isEgg)
{
	if (m_IsEgg != isEgg)
	{
		m_IsEgg = isEgg;
		auto components = m_pOwner->GetComponents<SingleRowAnimationComponent>();
		for (size_t i = 0; i < components.size(); i++)
		{
			components[i]->SetDoRender(!components[i]->GetDoRender());
			components[i]->SetFrame(0);
		}
	}
}

void CoilyJumperComponent::ConnectJumpCommands()
{
	m_JumpUpLeft->Bind(this);
	m_JumpUpRight->Bind(this);
	m_JumpDownRight->Bind(this);
	m_JumpDownLeft->Bind(this);

}

void CoilyJumperComponent::DisconnectJumpCommands()
{
	m_JumpUpLeft->Bind(nullptr);
	m_JumpUpRight->Bind(nullptr);
	m_JumpDownRight->Bind(nullptr);
	m_JumpDownLeft->Bind(nullptr);
}

void CoilyJumperComponent::JumpToClosestQbert()
{
	assert(m_Qbert1->IsActive());
	
	auto jumperQbert1 = m_Qbert1->GetComponent<QbertJumperComponent>();
	glm::ivec2 distance1 = jumperQbert1->GetPos() - GetPos();

	if (!m_Qbert2->IsActive())
	{
		distance1.x = sgn(distance1.x);
		if (distance1.x == 0)
		{
			if (distance1.y > 0)
				distance1.x = -1;
			else
				distance1.x = 1;
		}

		distance1.y = sgn(distance1.y);
		if (distance1.y == 0)
		{
			if (m_pLevel->GetTile(distance1.x, GetPos().y + 1) == nullptr)
				distance1.y = -1;
			else
				distance1.y = 1;
		}

		Jump(distance1.x, distance1.y);
		return;
	}

	auto jumperQbert2 = m_Qbert2->GetComponent<QbertJumperComponent>();
	glm::ivec2 distance2 = jumperQbert2->GetPos() - GetPos();

	if (distance1.x + distance1.y < distance2.x + distance2.y)
	{
		distance1.x = sgn(distance1.x);
		if (distance1.x == 0)
		{
			if (distance1.y > 0)
				distance1.x = -1;
			else
				distance1.x = 1;
		}

		distance1.y = sgn(distance1.y);
		if (distance1.y == 0)
		{
			if (m_pLevel->GetTile(distance1.x, GetPos().y + 1) == nullptr)
				distance1.y = -1;
			else
				distance1.y = 1;
		}

		Jump(distance1.x, distance1.y);
		return;
	}
	else
	{
		distance2.x = sgn(distance2.x);
		if (distance2.x == 0)
		{
			if (distance2.y > 0)
				distance2.x = -1;
			else
				distance2.x = 1;
		}

		distance2.y = sgn(distance2.y);
		if (distance2.y == 0)
		{
			if (m_pLevel->GetTile(distance2.x, GetPos().y + 1) == nullptr)
				distance2.y = -1;
			else
				distance2.y = 1;
		}

		Jump(distance2.x, distance2.y);
		return;
	}

}
