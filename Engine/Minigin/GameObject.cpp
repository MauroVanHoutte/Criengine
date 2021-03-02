#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "BaseComponent.h"

dae::GameObject::~GameObject()
{
	for (auto it = m_ComponentMap.begin(); it != m_ComponentMap.end(); it++)
	{
		delete it->second;
	}
}

void dae::GameObject::Update()
{
	for (auto it = m_ComponentMap.begin(); it != m_ComponentMap.end(); it++)
	{
		it->second->Update();
	}
}

void dae::GameObject::FixedUpdate()
{
	for (auto it = m_ComponentMap.begin(); it != m_ComponentMap.end(); it++)
	{
		it->second->FixedUpdate();
	}
}

void dae::GameObject::LateUpdate()
{
	for (auto it = m_ComponentMap.begin(); it != m_ComponentMap.end(); it++)
	{
		it->second->LateUpdate();
	}
}

void dae::GameObject::Render() const
{
	const auto pos = m_Transform.GetPosition();

	for (auto it = m_ComponentMap.begin(); it != m_ComponentMap.end(); it++)
	{
		it->second->Render();
	}
}

void dae::GameObject::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}

bool dae::GameObject::AddComponent(const std::string& name, BaseComponent* component)
{
	if (m_ComponentMap.find(name) == m_ComponentMap.end())
	{
		m_ComponentMap[name] = component;
		return true;
	}
	
	std::cout << "Component with name " << name << " already exists in this object\n";
	return false;
}

bool dae::GameObject::RemoveComponent(const std::string& name)
{
	auto it = m_ComponentMap.find(name);
	if (it == m_ComponentMap.end())
	{
		return false;
	}
	m_ComponentMap.erase(it);
	return true;
}

std::map<std::string, BaseComponent*>& dae::GameObject::GetComponents()
{
	return m_ComponentMap;
}
