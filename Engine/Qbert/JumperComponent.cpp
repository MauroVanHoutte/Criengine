#include "JumperComponent.h"
#include "Level.h"
#include <Timer.h>
#include <GameObject.h>
#include "TileTextureComponent.h"

JumperComponent::JumperComponent(cri::GameObject* pOwner, Level* pLevel, int starRow, int startCol)
	: BaseComponent(pOwner)
	, m_pLevel{pLevel}
	, m_Pos{startCol, starRow}
	, m_JumpStartPos{0.f, 0.f}
	, m_Target{ nullptr }
	, m_JumpDuration{1.f}
	, m_JumpDurationOffMap{5.f}
	, m_JumpDurationTile{1.f}
	, m_JumpCounter{0.f}
	, m_IsJumping{false}
	, m_Gravity{120.f}
{
	auto startTile = m_pLevel->GetTile(m_Pos.x, m_Pos.y);
	float yOffset = -30.f;
	m_pOwner->m_Transform.SetPosition(startTile->m_Transform.GetPosition().x, startTile->m_Transform.GetPosition().y + yOffset, 0);
}

void JumperComponent::Update()
{
	if (m_IsJumping)
	{
		float deltaTime = Timer::GetInstance()->GetElapsed();
		m_JumpCounter += deltaTime;

		if (m_JumpCounter > m_JumpDuration)
		{
			m_JumpCounter = m_JumpDuration;
			m_IsJumping = false;
			if (m_Target)
			{
				m_Target->GetComponent<TileTextureComponent>()->JumpedOn();
			}
		}
		
		float newX = m_JumpStartPos.x + m_JumpCounter * m_InitialJumpVelocity.x;
		float newY = m_JumpStartPos.y + m_JumpCounter * m_InitialJumpVelocity.y + 0.5f * m_Gravity * m_JumpCounter * m_JumpCounter;
		m_pOwner->m_Transform.SetPosition(newX, newY, 0);
	}
}

void JumperComponent::Jump(int colDir, int rowDir)
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


	m_Target = m_pLevel->GetTile(m_Pos.x + newColDir, m_Pos.y + rowDir);
	if (m_Target == nullptr)
	{
		JumpOffMap(colDir, rowDir);
	}
	else
	{
		float yOffset = -30.f;
		m_JumpCounter = 0.f;
		auto position = m_pOwner->m_Transform.GetPosition();
		m_InitialJumpVelocity.x = (m_Target->m_Transform.GetPosition().x - position.x)/m_JumpDuration;
		m_InitialJumpVelocity.y = -(-(m_Target->m_Transform.GetPosition().y + yOffset - position.y) + 0.5f * m_Gravity * m_JumpDuration * m_JumpDuration) / m_JumpDuration;
		m_JumpStartPos.x = position.x;
		m_JumpStartPos.y = position.y;
		m_Pos.x += newColDir;
		m_Pos.y += rowDir;
		m_IsJumping = true;
		m_JumpDuration = m_JumpDurationTile;
	}

}

void JumperComponent::JumpOffMap(int colDir, int rowDir)
{
	m_InitialJumpVelocity.x = colDir * 30.f;
	if (rowDir > 0)
	{
		m_InitialJumpVelocity.y = -20.f;
	}
	else
	{
		m_InitialJumpVelocity.y = -100.f;
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
