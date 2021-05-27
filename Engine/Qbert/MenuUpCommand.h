#pragma once
#include <Command.h>
#include "QbertMainMenuComponent.h"

class MenuUpCommand : public Command
{
public:
	MenuUpCommand();
	void Bind(QbertMainMenuComponent* menuComp);

	void Execute() override;

private:
	QbertMainMenuComponent* m_Menu;

};