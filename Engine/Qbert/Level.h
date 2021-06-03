#pragma once
#include <vector>
#include <GameObject.h>
#include <memory>
#include <Scene.h>

class QbertGame;
class Level
{
public:
	Level(int height, int difficulty, int tileSize, float topX, float topY, cri::Scene& scene, const std::string& tileTexture, QbertGame* manager);
	Level() = delete;
	~Level();

	void AddTile(std::shared_ptr<cri::GameObject> tile);
	std::shared_ptr<cri::GameObject> GetTile(int x, int y);

	int GetHeight();

	bool Completed();

private:
	int m_Height;
	int m_Difficulty;
	int m_TileSize;
	std::vector<std::shared_ptr<cri::GameObject>> m_Tiles;
};