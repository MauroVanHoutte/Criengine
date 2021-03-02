#pragma once
#include "Command.h"
#include "QbertHealthComponent.h"

class QbertDeathCommand : public Command
{
public:
	QbertDeathCommand(QbertHealthComponent* qbertHealthComponent);
	void Execute() override;
private:
	QbertHealthComponent* m_pHealthComponent;
};