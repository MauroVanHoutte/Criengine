#include "QbertMainMenuComponent.h"
#include <ResourceManager.h>
#include <TextRenderer.h>
#include <TextureComponent.h>


QbertMainMenuComponent::QbertMainMenuComponent(cri::GameObject* pOwner)
	: BaseComponent(pOwner)
	, m_NrMenuOptions{3}
	, m_SelectedMenuOption{0}
{
	m_QBertTexture = new TextureComponent(pOwner);
	m_QBertTexture->SetTexture(cri::ResourceManager::GetInstance().LoadTexture("singleQbert.png"));
	m_QBertTexture->m_RelativeTransform.SetPosition(-30.f, -25.f, 0);
	m_QBertTexture->SetHeight(20.f);
	m_QBertTexture->SetWidth(20.f);
	TextRenderer::GetInstance()->AddFont("Pixeboy.ttf", 24, { 255, 255, 255 });

}

QbertMainMenuComponent::~QbertMainMenuComponent()
{
}

void QbertMainMenuComponent::Render() const
{
	auto position = m_pOwner->m_Transform.GetPosition();
	TextRenderer::GetInstance()->RenderString("1 PLAYER", glm::vec3{ position.x, position.y -30.f, 0.f }, "Pixeboy.ttf", 24, { 255,255,255 });
	TextRenderer::GetInstance()->RenderString("2 PLAYER", glm::vec3{ position.x, position.y, 0.f }, "Pixeboy.ttf", 24, { 255,255,255 });
	TextRenderer::GetInstance()->RenderString("1 V 1", glm::vec3{ position.x, position.y + 30.f, 0.f }, "Pixeboy.ttf", 24, { 255,255,255 });
	m_QBertTexture->Render();
}

void QbertMainMenuComponent::MenuOptionUp()
{
	--m_SelectedMenuOption;
	auto pos = m_QBertTexture->m_RelativeTransform.GetPosition();
	m_QBertTexture->m_RelativeTransform.SetPosition(pos.x, pos.y - 30.f, pos.z);

	if (m_SelectedMenuOption < 0)
	{
		m_SelectedMenuOption = m_NrMenuOptions - 1;
		m_QBertTexture->m_RelativeTransform.SetPosition(pos.x, pos.y + 60.f, pos.z);
	}
}

void QbertMainMenuComponent::MenuOptionDown()
{
	++m_SelectedMenuOption;
	auto pos = m_QBertTexture->m_RelativeTransform.GetPosition();
	m_QBertTexture->m_RelativeTransform.SetPosition(pos.x, pos.y + 30.f, pos.z);

	if (m_SelectedMenuOption >= m_NrMenuOptions)
	{
		m_SelectedMenuOption = 0;
		m_QBertTexture->m_RelativeTransform.SetPosition(pos.x, pos.y - 60.f, pos.z);
	}
}

void QbertMainMenuComponent::ButtonClicked()
{
	switch (m_SelectedMenuOption)
	{
	case 0:
		Notify(Event::StartSinglePlayer);
		break;
	case 1:
		Notify(Event::StartCoop);
		break;
	case 2:
		Notify(Event::StartVersus);
		break;
	default:
		break;
	}
}
