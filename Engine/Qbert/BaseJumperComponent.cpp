#include "BaseJumperComponent.h"
#include "Level.h"
#include <Timer.h>
#include <GameObject.h>
#include "TileTextureComponent.h"
#include "SingleRowAnimationComponent.h"
#include "ServiceLocator.h"

BaseJumperComponent::BaseJumperComponent(cri::GameObject* pOwner, float jumpDuration, const std::string& jumpSoundName, const std::string& fallSoundName)
	: BaseComponent(pOwner)
	, m_pLevel{ nullptr }
	, m_Pos{ 0, 0 }
	, m_JumpStartPos{ 0.f, 0.f }
	, m_Target{ nullptr }
	, m_JumpDuration{ jumpDuration }
	, m_JumpDurationOffMap{ 3.f }
	, m_JumpDurationTile{ jumpDuration }
	, m_JumpCounter{ 0.f }
	, m_IsJumping{ false }
	, m_Gravity{ 280.f }
	, m_JumpSoundName{ jumpSoundName }
	, m_FallSoundName{ fallSoundName }
{
}

void BaseJumperComponent::Update()
{
	if (m_IsJumping)
	{
		float deltaTime = Timer::GetInstance()->GetElapsed();
		m_JumpCounter += deltaTime;

		if (m_JumpCounter > m_JumpDuration)
		{
			m_JumpCounter = m_JumpDuration;
			m_IsJumping = false;

		}

		float newX = m_JumpStartPos.x + m_JumpCounter * m_InitialJumpVelocity.x;
		float newY = m_JumpStartPos.y + m_JumpCounter * m_InitialJumpVelocity.y + 0.5f * m_Gravity * m_JumpCounter * m_JumpCounter;
		m_pOwner->m_Transform.SetPosition(newX, newY, 0);
		if (!m_IsJumping)
		{
			if (m_Target)
			{
				JumpedOn();
			}

			m_pOwner->GetComponent<SingleRowAnimationComponent>()->NextFrame();
			if (m_JumpDuration > m_JumpDurationTile)
			{
				JumpedOff();
			}
		}
	}
}

void BaseJumperComponent::Jump(int colDir, int rowDir)
{
	if (m_IsJumping)
	{
		return;
	}

	int newColDir = colDir;

	if (colDir < 0 && rowDir > 0)
	{
		newColDir = colDir + 1;
	}

	if (colDir > 0 && rowDir < 0)
	{
		newColDir = colDir - 1;
	}

	HandleAnimation(colDir, rowDir);

	m_Target = m_pLevel->GetTile(m_Pos.x + newColDir, m_Pos.y + rowDir);
	if (m_Target == nullptr)
	{
		ServiceLocator::GetSoundSystem()->Play(m_FallSoundName, 0, 5);
		JumpOffMap(colDir, rowDir);
	}
	else
	{
		ServiceLocator::GetSoundSystem()->Play(m_JumpSoundName, 0, 5);
		m_JumpDuration = m_JumpDurationTile;
		float yOffset = -30.f;
		m_JumpCounter = 0.f;
		auto position = m_pOwner->m_Transform.GetPosition();
		m_InitialJumpVelocity.x = (m_Target->m_Transform.GetPosition().x - position.x) / m_JumpDuration;
		m_InitialJumpVelocity.y = -(-(m_Target->m_Transform.GetPosition().y + yOffset - position.y) + 0.5f * m_Gravity * m_JumpDuration * m_JumpDuration) / m_JumpDuration;
		m_JumpStartPos.x = position.x;
		m_JumpStartPos.y = position.y;
		m_Pos.x += newColDir;
		m_Pos.y += rowDir;
		m_IsJumping = true;
	}
}

void BaseJumperComponent::SetStartPos(Level* pLevel, int startRow, int startCol)
{
	m_pLevel = pLevel;
	m_Pos.x = startCol;
	m_Pos.y = startRow;
	auto startTile = m_pLevel->GetTile(m_Pos.x, m_Pos.y);
	cri::SceneManager::GetInstance().GetCurrentScene().MoveObjectToFront(m_pOwner);
	HandleStartPos(startTile);
	m_IsJumping = false;
}

void BaseJumperComponent::JumpOffMap(int colDir, int rowDir)
{
	m_InitialJumpVelocity.x = colDir * 30.f;
	if (rowDir > 0)
	{
		m_InitialJumpVelocity.y = -20.f;
	}
	else
	{
		m_InitialJumpVelocity.y = -100.f;
		cri::SceneManager::GetInstance().GetCurrentScene().MoveObjectToBack(m_pOwner);
	}
	m_JumpCounter = 0.f;
	auto position = m_pOwner->m_Transform.GetPosition();
	m_JumpStartPos.x = position.x;
	m_JumpStartPos.y = position.y;
	m_Pos.x += colDir;
	m_Pos.y += rowDir;
	m_IsJumping = true;
	m_JumpDuration = m_JumpDurationOffMap;
}
