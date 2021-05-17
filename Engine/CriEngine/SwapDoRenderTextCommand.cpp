#include "SwapDoRenderTextCommand.h"

void SwapDoRenderTextCommand::Execute()
{
	m_TextComponent->SwapDoRender();
}

void SwapDoRenderTextCommand::Bind(TextComponent* textComponent)
{
	m_TextComponent = textComponent;
}
