#include "MiniginPCH.h"
#include "QbertDeathCommand.h"

QbertDeathCommand::QbertDeathCommand(QbertHealthComponent* qbertHealthComponent)
	:m_pHealthComponent{qbertHealthComponent}
{
}

void QbertDeathCommand::Execute()
{
	m_pHealthComponent->Death();
}
