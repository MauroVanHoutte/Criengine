#include "Level.h"
#include "TileTextureComponent.h"
#include "Qbert.h"
#include <chrono>
#include <iostream>
#include "DiskComponent.h"
#include "SingleRowAnimationComponent.h"
#include <ResourceManager.h>

Level::Level(int height, int difficulty, int tileSize, float topX, float topY, int leftDiskRow, int rightDiskRow, cri::Scene& scene, const std::string& texture, QbertGame* manager)
	: m_Height{height}
	, m_Difficulty{difficulty}
	, m_TileSize{tileSize}
	, m_LeftDiskCoord{-1, leftDiskRow}
	, m_RightDiskCoord{rightDiskRow+1, rightDiskRow}
{
	auto timeStart = std::chrono::high_resolution_clock::now();
	for (int r = 0; r < height; r++)
	{
		for (int c = 0; c <= r; c++)
		{
			float yPos{ topY + tileSize * r * 0.72f };
			float xPos{ topX - tileSize * r * 0.5f + tileSize * c };

			auto tile = std::make_shared<cri::GameObject>();
			tile->m_Transform.SetPosition(xPos, yPos);
			TileTextureComponent* tileTexture = new TileTextureComponent(tile.get(), texture);
			tileTexture->SetWidth(float(tileSize));
			tileTexture->SetHeight(float(tileSize));
			tileTexture->SetDifficulty(difficulty);
			tileTexture->AddObserver(manager);

			m_Tiles.push_back(tile);
			scene.Add(tile);
		}
		if (r == leftDiskRow)
		{
			m_LeftDisk = std::make_shared<cri::GameObject>();
			float yPos{ topY + tileSize * r * 0.72f };
			float xPos{ topX - tileSize * r * 0.5f + tileSize * -1 };
			float diskTargetY{ topY + tileSize * -2 * 0.72f };
			m_LeftDisk->m_Transform.SetPosition(xPos, yPos);
			new DiskComponent(m_LeftDisk.get(), { topX, diskTargetY });
			auto textureComp = new SingleRowAnimationComponent(m_LeftDisk.get(), 1, 4, cri::ResourceManager::GetInstance().LoadTexture("DiskSpriteSheet.png"));
			textureComp->SetWidth(30.f);
			textureComp->SetHeight(30.f);
			scene.Add(m_LeftDisk);
		}
		if (r == rightDiskRow)
		{
			m_RightDisk = std::make_shared<cri::GameObject>();
			float yPos{ topY + tileSize * r * 0.72f };
			float xPos{ topX - tileSize * r * 0.5f + tileSize * (r+1) };
			float diskTargetY{ topY + tileSize * -2 * 0.72f };
			m_RightDisk->m_Transform.SetPosition(xPos, yPos);
			new DiskComponent(m_RightDisk.get(), { topX, diskTargetY });
			auto textureComp = new SingleRowAnimationComponent(m_RightDisk.get(), 1, 4, cri::ResourceManager::GetInstance().LoadTexture("DiskSpriteSheet.png"));
			textureComp->SetWidth(30.f);
			textureComp->SetHeight(30.f);
			scene.Add(m_RightDisk);
		}
	}
	auto timeEnd = std::chrono::high_resolution_clock::now();
	std::cout << "Level set up in " << std::chrono::duration<float>(timeEnd - timeStart).count() << " seconds\n";
}

Level::~Level()
{
	m_LeftDisk->MarkForDeletion();
	m_RightDisk->MarkForDeletion();
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

std::shared_ptr<cri::GameObject> Level::GetTile(int column, int row, bool canUseDisk)
{
	if (canUseDisk && column == m_LeftDiskCoord.x && row == m_LeftDiskCoord.y)
	{
		return m_LeftDisk;
	}
	if (canUseDisk && column == m_RightDiskCoord.x && row == m_RightDiskCoord.y)
	{
		return m_RightDisk;
	}

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

int Level::NrActiveDisks()
{
	int active{ 0 };
	if (m_LeftDisk->IsActive())
	{
		active += 1;
	}
	if (m_RightDisk->IsActive())
	{
		active += 1;
	}
	return active;
}
