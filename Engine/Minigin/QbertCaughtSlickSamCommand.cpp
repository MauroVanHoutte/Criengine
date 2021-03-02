#include "MiniginPCH.h"
#include "QbertCaughtSlickSamCommand.h"

QbertCaughtSlickSamCommand::QbertCaughtSlickSamCommand(QbertScoreComponent* component)
	:m_Component(component)
{
}

void QbertCaughtSlickSamCommand::Execute()
{
	m_Component->CaughtSlickSam();
}
