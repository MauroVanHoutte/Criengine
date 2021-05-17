#include "QbertRemainingDiscCommand.h"

QbertRemainingDiscCommand::QbertRemainingDiscCommand(QbertScoreComponent* component)
	: m_Component(component)
{
}

void QbertRemainingDiscCommand::Execute()
{
	m_Component->RemainingDisc();
}
