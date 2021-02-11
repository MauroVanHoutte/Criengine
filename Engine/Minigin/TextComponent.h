#pragma once
#include "BaseComponent.h"
#include "Transform.h"
#include "Font.h"
#include "Texture2D.h"

#include <string>



class TextComponent : public BaseComponent
{
public:
	TextComponent(dae::GameObject* owner, const std::string& text, const std::string& font, int fontSize, const glm::vec3& pos);
	virtual ~TextComponent();

	void SetPosition(const glm::vec3& pos);
	const glm::vec3& GetPosition() const;

	void SetText(const std::string& text);

	void Render() const override;

private:
	dae::Transform m_Transform;
	dae::Texture2D* m_pTexture;
	dae::Font* m_pFont;
};