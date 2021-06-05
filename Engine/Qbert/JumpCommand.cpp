#include "JumpCommand.h"
#include <assert.h>

JumpCommand::JumpCommand(int colDir, int rowDir)
	: m_pJumper{nullptr}
	, m_ColDirection{colDir}
	, m_RowDirection{rowDir}
{
}

void JumpCommand::Execute()
{
	if (!m_pJumper)
		return;
	if (m_pJumper->IsOwnerActive() && m_pJumper->IsActive())
	{
		m_pJumper->Jump(m_ColDirection, m_RowDirection);
	}
}

void JumpCommand::Bind(BaseJumperComponent* jumper)
{
	m_pJumper = jumper;
}
