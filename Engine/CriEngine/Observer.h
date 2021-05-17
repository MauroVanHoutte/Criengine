#pragma once

enum class Event
{
	PlayerDeath,
	ColorChange,
	CoilyDeath,
	RemainingDisc,
	SlickSamCaught
};

class Observer
{
public:
	virtual ~Observer() = default;
	virtual void OnNotify( Event event) = 0;
};
