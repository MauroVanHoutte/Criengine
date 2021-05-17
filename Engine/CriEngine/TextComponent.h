#pragma once
#include "BaseComponent.h"
#include "Transform.h"
#include "Font.h"
#include "Texture2D.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>



class TextComponent : public BaseComponent
{
public:
	TextComponent(cri::GameObject* owner, const std::string& text, const std::string& font, int fontSize, const glm::vec3& pos, const glm::vec3& color);
	virtual ~TextComponent();

	void SetPosition(const glm::vec3& pos);
	const glm::vec3& GetPosition() const;

	void SetText(const std::string& text);
	void SetColor(const glm::vec3& color);
	void SetFont(const std::string& font);
	void SetSize(int size);

	void Render() const override;
	void SwapDoRender();

private:
	std::string m_Text;
	SDL_Color m_Color;
	cri::Transform m_Transform;
	std::string m_Font;
	int m_FontSize;

protected:
	bool m_DoRender;
};