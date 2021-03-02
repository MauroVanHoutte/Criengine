#include "MiniginPCH.h"
#include "QbertCoilyDeathCommand.h"

QbertCoilyDeathCommand::QbertCoilyDeathCommand(QbertScoreComponent* component)
	: m_Component(component)
{
}

void QbertCoilyDeathCommand::Execute()
{
	m_Component->CoilyDeath();
}
