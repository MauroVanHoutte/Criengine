#pragma once
#include "Command.h"
#include "QbertScoreComponent.h"

class QbertRemainingDiscCommand : public Command
{
public:
	QbertRemainingDiscCommand(QbertScoreComponent* component);

	void Execute() override;
private:
	QbertScoreComponent* m_Component;
};