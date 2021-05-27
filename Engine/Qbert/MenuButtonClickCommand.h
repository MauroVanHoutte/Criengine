#pragma once
#include <Command.h>
#include "QbertMainMenuComponent.h"

class MenuButtonClickCommand : public Command
{
public:
	MenuButtonClickCommand();

	void Bind(QbertMainMenuComponent* menu);
	void Execute() override;

private:
	QbertMainMenuComponent* m_Menu;

};