#pragma once
#include <vector>
#include <GameObject.h>
#include <memory>
#include <Scene.h>
#include <glm/vec2.hpp>

class QbertGame;
class Level
{
public:
	Level(int height, int difficulty, int tileSize, float topX, float topY, int leftDiskRow, int rightDiskRow, cri::Scene& scene, const std::string& tileTexture, QbertGame* manager);
	Level() = delete;
	~Level();

	void AddTile(std::shared_ptr<cri::GameObject> tile);
	std::shared_ptr<cri::GameObject> GetTile(int x, int y, bool canUseDisk);

	int GetHeight();

	bool Completed();

	int NrActiveDisks();

private:
	int m_Height;
	int m_Difficulty;
	int m_TileSize;
	std::vector<std::shared_ptr<cri::GameObject>> m_Tiles;
	std::shared_ptr<cri::GameObject> m_LeftDisk;
	glm::ivec2 m_LeftDiskCoord;
	std::shared_ptr<cri::GameObject> m_RightDisk;
	glm::ivec2 m_RightDiskCoord;
};