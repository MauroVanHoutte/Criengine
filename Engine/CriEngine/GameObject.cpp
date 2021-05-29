#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "BaseComponent.h"
#include <iostream>

cri::GameObject::~GameObject()
{
	for (auto it = m_ComponentMap.begin(); it != m_ComponentMap.end(); it++)
	{
		delete it->second;
	}
}

void cri::GameObject::Update()
{
	if (!m_Active)
	{
		return;
	}
	for (auto it = m_ComponentMap.begin(); it != m_ComponentMap.end(); it++)
	{
		if (it->second->IsActive())
			it->second->Update();
	}
}

void cri::GameObject::FixedUpdate()
{
	if (!m_Active)
	{
		return;
	}
	for (auto it = m_ComponentMap.begin(); it != m_ComponentMap.end(); it++)
	{
		if (it->second->IsActive())
			it->second->FixedUpdate();
	}
}

void cri::GameObject::LateUpdate()
{
	if (!m_Active)
	{
		return;
	}
	for (auto it = m_ComponentMap.begin(); it != m_ComponentMap.end(); it++)
	{
		if (it->second->IsActive())
			it->second->LateUpdate();
	}
}

void cri::GameObject::Render() const
{
	if (!m_Active)
	{
		return;
	}
	const auto pos = m_Transform.GetPosition();

	for (auto it = m_ComponentMap.begin(); it != m_ComponentMap.end(); it++)
	{
		if (it->second->IsActive())
			it->second->Render();
	}
}

void cri::GameObject::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}

bool cri::GameObject::AddComponent(const std::string& name, BaseComponent* component)
{
	if (m_ComponentMap.find(name) == m_ComponentMap.end())
	{
		m_ComponentMap[name] = component;
		return true;
	}
	
	std::cout << "Component with name " << name << " already exists in this object\n";
	return false;
}

bool cri::GameObject::RemoveComponent(const std::string& name)
{
	auto it = m_ComponentMap.find(name);
	if (it == m_ComponentMap.end())
	{
		return false;
	}
	m_ComponentMap.erase(it);
	return true;
}

std::map<std::string, BaseComponent*>& cri::GameObject::GetComponents()
{
	return m_ComponentMap;
}
