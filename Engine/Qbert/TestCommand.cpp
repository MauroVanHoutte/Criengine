#include "TestCommand.h"
#include <iostream>

TestCommand::TestCommand(const std::string& testMessage)
	: m_Message{testMessage}
{
}

void TestCommand::Execute()
{
	std::cout << m_Message << std::endl;
}
