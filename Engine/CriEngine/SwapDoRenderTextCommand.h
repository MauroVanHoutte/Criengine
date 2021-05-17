#pragma once
#include "Command.h"
#include "TextComponent.h"

class SwapDoRenderTextCommand : public Command
{
public:
	void Execute() override;
	void Bind(TextComponent* textComponent);
private:
	TextComponent* m_TextComponent = nullptr;
};
