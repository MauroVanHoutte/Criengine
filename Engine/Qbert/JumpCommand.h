#pragma once
#include <Command.h>
#include "BaseJumperComponent.h"


class JumpCommand : public Command
{
public:
	JumpCommand(int colDir, int rowDir);

	void Execute() override;
	void Bind(BaseJumperComponent* jumper);
private:
	BaseJumperComponent* m_pJumper;
	int m_ColDirection;
	int m_RowDirection;
};
