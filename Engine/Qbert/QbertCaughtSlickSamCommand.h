#pragma once
#include "Command.h"
#include "QbertScoreComponent.h"

class QbertCaughtSlickSamCommand : public Command
{
public:
	QbertCaughtSlickSamCommand(QbertScoreComponent* component);

	void Execute() override;
private:
	QbertScoreComponent* m_Component;
};