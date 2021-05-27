#include "MenuButtonClickCommand.h"

MenuButtonClickCommand::MenuButtonClickCommand()
{
}

void MenuButtonClickCommand::Bind(QbertMainMenuComponent* menu)
{
	m_Menu = menu;
}

void MenuButtonClickCommand::Execute()
{
	m_Menu->ButtonClicked();
}
