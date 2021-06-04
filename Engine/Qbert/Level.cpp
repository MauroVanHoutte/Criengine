#include "Level.h"
#include "TileTextureComponent.h"
#include "Qbert.h"
#include <chrono>
#include <iostream>

Level::Level(int height, int difficulty, int tileSize, float topX, float topY, cri::Scene& scene, const std::string& texture, QbertGame* manager)
	: m_Height{height}
	, m_Difficulty{difficulty}
	, m_TileSize{tileSize}
{
	auto timeStart = std::chrono::high_resolution_clock::now();
	for (int r = 0; r < height; r++)
	{
		for (int c = 0; c <= r; c++)
		{
			float yPos{ topY + tileSize * r * 0.72f };
			float xPos{ topX - tileSize * r * 0.5f + tileSize * c };

			auto tile = std::make_shared<cri::GameObject>();
			tile->m_Transform.SetPosition(xPos, yPos, 0);
			TileTextureComponent* tileTexture = new TileTextureComponent(tile.get(), texture);
			tileTexture->SetWidth(float(tileSize));
			tileTexture->SetHeight(float(tileSize));
			tileTexture->SetDifficulty(difficulty);
			tileTexture->AddObserver(manager);

			m_Tiles.push_back(tile);
			scene.Add(tile);
		}
	}
	auto timeEnd = std::chrono::high_resolution_clock::now();
	std::cout << "Level set up in " << std::chrono::duration<float>(timeEnd - timeStart).count() << " seconds\n";
}

Level::~Level()
{

	for  (size_t i = 0; i < m_Tiles.size(); ++i)
	{
		if (m_Tiles[i] != nullptr)
		{
			m_Tiles[i]->MarkForDeletion();
		}
	}
}

void Level::AddTile(std::shared_ptr<cri::GameObject> tile)
{
	m_Tiles.push_back(tile);
}

std::shared_ptr<cri::GameObject> Level::GetTile(int column, int row)
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

int Level::GetHeight()
{
	return m_Height;
}

bool Level::Completed()
{
	for (auto tile : m_Tiles)
	{
		if (!tile->GetComponent<TileTextureComponent>()->IsCorrect())
		{
			return false;
		}
	}
	return true;
}
