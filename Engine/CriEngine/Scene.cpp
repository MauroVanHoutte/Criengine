#include "Scene.h"
#include "GameObject.h"
#include <string>
#include "SceneObject.h"

using namespace cri;

unsigned int Scene::m_IdCounter = 0;

void cri::Scene::MoveObjectToFront(SceneObject* object) //front of the scene, back of the deque
{
	auto it = std::find_if(m_Objects.begin(), m_Objects.end(), [object](std::shared_ptr<cri::SceneObject> sceneObject) {return object == sceneObject.get(); });
	if (it == m_Objects.end())
	{
		bool breakpoint{true};
		breakpoint = false;
	}

	auto temp = *it;
	m_Objects.erase(std::remove_if(m_Objects.begin(), m_Objects.end(), [object](std::shared_ptr<cri::SceneObject> sceneObject) {return object == sceneObject.get(); }));
	m_Objects.push_back(temp);
}

void cri::Scene::MoveObjectToBack(SceneObject* object) //back of the scene, front of the deque 
{
	auto it = std::find_if(m_Objects.begin(), m_Objects.end(), [object](std::shared_ptr<cri::SceneObject> sceneObject) {return object == sceneObject.get(); });
	auto temp = *it;
	m_Objects.erase(std::remove_if(m_Objects.begin(), m_Objects.end(), [object](std::shared_ptr<cri::SceneObject> sceneObject) {return object == sceneObject.get(); }));
	m_Objects.push_front(temp);
}

Scene::Scene(const std::string& name) : m_Name(name) {}

Scene::~Scene() = default;

void Scene::Add(const std::shared_ptr<SceneObject>& object)
{
	m_Objects.push_back(object);
}

void Scene::Update()
{
	for(size_t i = 0;  i < m_Objects.size(); ++i)
	{
		if (m_Objects[i]->IsActive())
			m_Objects[i]->Update();
	}
}

void cri::Scene::FixedUpdate()
{
	for (size_t i = 0; i < m_Objects.size(); ++i)
	{
		if (m_Objects[i]->IsActive())
			m_Objects[i]->FixedUpdate();
	}
}

void cri::Scene::LateUpdate()
{
	for (size_t i = 0; i < m_Objects.size(); ++i)
	{
		if (m_Objects[i]->IsActive())
			m_Objects[i]->LateUpdate();
	}
}

void Scene::Render() const
{
	for (size_t i = 0; i < m_Objects.size(); ++i)
	{
		if (m_Objects[i]->IsActive())
			m_Objects[i]->Render();
	}
}

void cri::Scene::DeletedMarkedObjects()
{
	m_Objects.erase(std::remove_if(m_Objects.begin(), m_Objects.end(), [](std::shared_ptr<cri::SceneObject> object) {return object->IsMarkedForDeletion(); }), m_Objects.end());
}

