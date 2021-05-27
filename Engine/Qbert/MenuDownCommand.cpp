#include "MenuDownCommand.h"

MenuDownCommand::MenuDownCommand()
{
}

void MenuDownCommand::Bind(QbertMainMenuComponent* menuComp)
{
	m_Menu = menuComp;
}

void MenuDownCommand::Execute()
{
	assert(m_Menu != nullptr);
	m_Menu->MenuOptionDown();
}
