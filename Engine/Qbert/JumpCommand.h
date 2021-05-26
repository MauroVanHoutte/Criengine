#pragma once
#include <Command.h>
#include "JumperComponent.h"


class JumpCommand : public Command
{
public:
	JumpCommand(int colDir, int rowDir);

	void Execute() override;
	void Bind(JumperComponent* jumper);
private:
	JumperComponent* m_pJumper;
	int m_ColDirection;
	int m_RowDirection;
};
