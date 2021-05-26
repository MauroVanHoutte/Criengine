#pragma once

class Level;
class QbertGame
{
public:

	static void Init();
	static void Cleanup();

private:

	QbertGame() = default;
	static Level* m_pLevel;
};