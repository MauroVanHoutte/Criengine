#include "Level.h"
#include "TileTextureComponent.h"

Level::Level(int height, int difficulty, int tileSize, float topX, float topY, cri::Scene& scene)
	: m_Height{height}
	, m_Difficulty{difficulty}
	, m_TileSize{tileSize}
{
	for (size_t r = 0; r < height; r++)
	{
		for (size_t c = 0; c <= r; c++)
		{
			float yPos{ topY + tileSize * r * 0.7f };
			float xPos{ topX - tileSize * r * 0.5f + tileSize * c };

			auto tile = std::make_shared<cri::GameObject>();
			tile->m_Transform.SetPosition(xPos, yPos, 0);
			TileTextureComponent* tileTexture = new TileTextureComponent(tile.get());
			tileTexture->SetWidth(float(tileSize));
			tileTexture->SetHeight(float(tileSize));
			tileTexture->SetDifficulty(difficulty);
			tile->AddComponent("TileTexture", tileTexture);

			m_Tiles.push_back(tile);
			scene.Add(tile);
		}
	}
}

void Level::AddTile(std::shared_ptr<cri::GameObject> tile)
{
	m_Tiles.push_back(tile);
}

std::shared_ptr<cri::GameObject> Level::GetTile(int row, int column)
{
	if (row < 0 || column < 0)
	{
		return nullptr;
	}
	if (row > m_Height-1 || column > row)
	{
		return nullptr;
	}

	int indexHeight{ (row * (row + 1)) / 2 };

	int index = indexHeight + column;
	return m_Tiles[index];
}
