#include "MenuUpCommand.h"
#include <assert.h>

MenuUpCommand::MenuUpCommand()
{
}

void MenuUpCommand::Bind(QbertMainMenuComponent* menuComp)
{
	m_Menu = menuComp;
}

void MenuUpCommand::Execute()
{
	assert(m_Menu != nullptr);
	m_Menu->MenuOptionUp();
}
