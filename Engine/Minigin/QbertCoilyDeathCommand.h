#pragma once
#include "Command.h"
#include "QbertScoreComponent.h"

class QbertCoilyDeathCommand : public Command
{
public:
	QbertCoilyDeathCommand(QbertScoreComponent* component);

	void Execute() override;
private:
	QbertScoreComponent* m_Component;
};