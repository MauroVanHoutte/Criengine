#pragma once
#include "BaseComponent.h"	
#include "Texture2D.h"
#include <memory>
#include "Transform.h"

class TextureComponent : public BaseComponent
{
public:
	TextureComponent(cri::GameObject* pOwner);

	void SetTexture(std::shared_ptr<cri::Texture2D> texture);

	void Render() const override;

	void SetHeight(float height);
	float GetHeight();
	void SetWidth(float width);
	float GetWidth();

	void SetDoRender(bool doRender);
	bool GetDoRender();

	cri::Transform m_RelativeTransform;
private:
	std::shared_ptr<cri::Texture2D> m_Texture;
	float m_Width;
	float m_Height;
	
protected:
	bool m_DoRender;
};