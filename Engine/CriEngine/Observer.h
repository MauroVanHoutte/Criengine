#pragma once

enum class Event
{
	PlayerDeath,
	ColorChange,
	CoilyDeath,
	RemainingDisc,
	SlickSamCaught,
	StartSinglePlayer,
	StartCoop,
	StartVersus,
	QbertDeath,
	GameStart
};

class Observer
{
public:
	virtual ~Observer() = default;
	virtual void OnNotify( Event event) = 0;
};
