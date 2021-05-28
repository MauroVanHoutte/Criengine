#pragma once
#include <Command.h>
#include <string>

class TestCommand : public Command
{
public:
	TestCommand(const std::string& testMessage);
	void Execute() override;
private:
	std::string m_Message;

};