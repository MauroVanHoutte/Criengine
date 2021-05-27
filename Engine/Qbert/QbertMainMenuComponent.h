#pragma once
#include <BaseComponent.h>
#include <Subject.h>

class TextureComponent;
class QbertMainMenuComponent : public BaseComponent, public Subject
{
public:
	QbertMainMenuComponent(cri::GameObject* pOwner);
	~QbertMainMenuComponent();

	void Render() const override;

	void MenuOptionUp();
	void MenuOptionDown();

	void ButtonClicked();

private:
	TextureComponent* m_QBertTexture;
	int m_SelectedMenuOption;
	int m_NrMenuOptions;
};