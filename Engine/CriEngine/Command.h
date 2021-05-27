#pragma once
class Command
{
public:
	explicit Command() = default;
	virtual ~Command() = default;
	virtual void Execute() = 0;
};