#pragma once
#include <TextureComponent.h>

class TileTextureComponent : public TextureComponent
{
public:
	TileTextureComponent(cri::GameObject* pOwner);
	TileTextureComponent() = delete;

	void SetDifficulty(int difficulty);
	void JumpedOn();

	void Render() const override;
	bool IsCorrect() const;
private:
	int m_TimesJumpedOn;
	int m_Difficulty;
};