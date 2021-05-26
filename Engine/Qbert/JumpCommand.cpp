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
	assert(m_pJumper != nullptr);
	m_pJumper->Jump(m_ColDirection, m_RowDirection);
}

void JumpCommand::Bind(JumperComponent* jumper)
{
	m_pJumper = jumper;
}
