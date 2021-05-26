#include "Scene.h"
#include "GameObject.h"
#include <string>

using namespace cri;

unsigned int Scene::m_IdCounter = 0;

void cri::Scene::MoveObjectToFront(std::shared_ptr<SceneObject> object)
{
	auto temp = m_Objects.back(); // front of rendering == rendered last
	auto it = std::find(m_Objects.begin(), m_Objects.end(), object); 
	m_Objects[it - m_Objects.begin()] = temp;
	m_Objects[m_Objects.size()-1] = object;
}

void cri::Scene::MoveObjectToBack(std::shared_ptr<SceneObject> object)
{
	auto temp = m_Objects.front(); // back of rendering == rendered first
	auto it = std::find(m_Objects.begin(), m_Objects.end(), object);
	m_Objects[it - m_Objects.begin()] = temp;
	m_Objects[0] = object;
}

Scene::Scene(const std::string& name) : m_Name(name) {}

Scene::~Scene() = default;

void Scene::Add(const std::shared_ptr<SceneObject>& object)
{
	m_Objects.push_back(object);
}

void Scene::Update()
{
	for(auto& object : m_Objects)
	{
		object->Update();
	}
}

void cri::Scene::FixedUpdate()
{
	for (auto& object : m_Objects)
	{
		object->FixedUpdate();
	}
}

void cri::Scene::LateUpdate()
{
	for (auto& object : m_Objects)
	{
		object->LateUpdate();
	}
}

void Scene::Render() const
{
	for (const auto& object : m_Objects)
	{
		object->Render();
	}
}

