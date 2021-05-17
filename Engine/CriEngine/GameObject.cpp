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
	for (auto it = m_ComponentMap.begin(); it != m_ComponentMap.end(); it++)
	{
		it->second->Update();
	}
}

void cri::GameObject::FixedUpdate()
{
	for (auto it = m_ComponentMap.begin(); it != m_ComponentMap.end(); it++)
	{
		it->second->FixedUpdate();
	}
}

void cri::GameObject::LateUpdate()
{
	for (auto it = m_ComponentMap.begin(); it != m_ComponentMap.end(); it++)
	{
		it->second->LateUpdate();
	}
}

void cri::GameObject::Render() const
{
	const auto pos = m_Transform.GetPosition();

	for (auto it = m_ComponentMap.begin(); it != m_ComponentMap.end(); it++)
	{
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
