#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "BaseComponent.h"
#include <iostream>

cri::GameObject::~GameObject()
{
	for (auto it = m_Components.begin(); it != m_Components.end(); it++)
	{
		delete *it;
	}
}

void cri::GameObject::Update()
{
	if (!m_Active) //is gameobject active
	{
		return;
	}
	for (auto it = m_Components.begin(); it != m_Components.end(); it++)
	{
		if ((*it)->IsActive()) //is component active
			(*it)->Update();
	}
}

void cri::GameObject::FixedUpdate()
{
	if (!m_Active)
	{
		return;
	}
	for (auto it = m_Components.begin(); it != m_Components.end(); it++)
	{
		if ((*it)->IsActive())
			(*it)->FixedUpdate();
	}
}

void cri::GameObject::LateUpdate()
{
	if (!m_Active)
	{
		return;
	}
	for (auto it = m_Components.begin(); it != m_Components.end(); it++)
	{
		if ((*it)->IsActive())
			(*it)->LateUpdate();
	}
}

void cri::GameObject::Render() const
{
	if (!m_Active)
	{
		return;
	}
	for (auto it = m_Components.begin(); it != m_Components.end(); it++)
	{
		if ((*it)->IsActive())
			(*it)->Render();
	}
}

void cri::GameObject::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y);
}

bool cri::GameObject::AddComponent(BaseComponent* component)
{
	assert(std::find(m_Components.begin(), m_Components.end(), component) == m_Components.end()); //component added twice
	
	m_Components.push_back(component);
	return false;
}

bool cri::GameObject::RemoveComponent(BaseComponent* component)
{
	auto it = std::find(m_Components.begin(), m_Components.end(), component);
	if (it != m_Components.end())
	{
		m_Components.erase(it);
		return true;
	}
	return false;
}

std::vector<BaseComponent*>& cri::GameObject::GetComponents()
{
	return m_Components;
}
