#include "Scene.h"
#include "GameObject.h"
#include <string>
#include "SceneObject.h"

using namespace cri;

unsigned int Scene::m_IdCounter = 0;

void cri::Scene::MoveObjectToFront(SceneObject* object)
{
	auto temp1 = m_Objects.back(); // front of rendering == rendered last
	auto it = std::find_if(m_Objects.begin(), m_Objects.end(), [object](std::shared_ptr<cri::SceneObject> sceneObject) {return object == sceneObject.get(); });
	auto temp2 = *it;
	m_Objects[it - m_Objects.begin()] = temp1;
	m_Objects[m_Objects.size()-1] = temp2;
}

void cri::Scene::MoveObjectToBack(SceneObject* object)
{
	auto temp1 = m_Objects.front(); // back of rendering == rendered first
	auto it = std::find_if(m_Objects.begin(), m_Objects.end(), [object](std::shared_ptr<cri::SceneObject> sceneObject) {return object == sceneObject.get(); });
	auto temp2 = *it;
	m_Objects[it - m_Objects.begin()] = temp1;
	m_Objects[0] = temp2;
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

void cri::Scene::DeletedMarkedObjects()
{
	m_Objects.erase(std::remove_if(m_Objects.begin(), m_Objects.end(), [](std::shared_ptr<cri::SceneObject> object) {return object->IsMarkedForDeletion(); }), m_Objects.end());
}

