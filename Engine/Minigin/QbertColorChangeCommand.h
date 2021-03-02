#pragma once
#include "Command.h"
#include "QbertScoreComponent.h"

class QbertColorChangeCommand : public Command
{
public:
	QbertColorChangeCommand(QbertScoreComponent* component );

	void Execute() override;
private:
	QbertScoreComponent* m_Component;
};