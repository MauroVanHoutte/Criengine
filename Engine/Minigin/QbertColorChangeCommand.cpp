#include "MiniginPCH.h"
#include "QbertColorChangeCommand.h"

QbertColorChangeCommand::QbertColorChangeCommand(QbertScoreComponent* component)
	:m_Component(component)
{
}

void QbertColorChangeCommand::Execute()
{
	m_Component->ColorChange();
}
