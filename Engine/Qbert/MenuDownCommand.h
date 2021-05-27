#pragma once
#include <Command.h>
#include "QbertMainMenuComponent.h"

class MenuDownCommand : public Command
{
public:
	MenuDownCommand();
	void Bind(QbertMainMenuComponent* menuComp);

	void Execute() override;

private:
	QbertMainMenuComponent* m_Menu;

};