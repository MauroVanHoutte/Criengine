#include "SceneManager.h"
#include "Scene.h"
#include <assert.h>

void cri::SceneManager::Update()
{
	assert(m_CurrentSceneIdx > -1);
	m_Scenes[m_CurrentSceneIdx]->Update();
}

void cri::SceneManager::FixedUpdate()
{
	assert(m_CurrentSceneIdx > -1);
	m_Scenes[m_CurrentSceneIdx]->FixedUpdate();
}

void cri::SceneManager::LateUpdate()
{
	assert(m_CurrentSceneIdx > -1);
	m_Scenes[m_CurrentSceneIdx]->LateUpdate();
}

void cri::SceneManager::Render()
{
	assert(m_CurrentSceneIdx > -1);
	m_Scenes[m_CurrentSceneIdx]->Render();
}

cri::Scene& cri::SceneManager::CreateScene(const std::string& name)
{
	const auto scene = std::shared_ptr<Scene>(new Scene(name));
	m_CurrentSceneIdx = int(m_Scenes.size());
	m_Scenes.push_back(scene);
	return *scene;
}

void cri::SceneManager::NextScene()
{
	++m_CurrentSceneIdx;
	if (m_CurrentSceneIdx >= m_Scenes.size())
	{
		m_CurrentSceneIdx = 0;
	}
}

void cri::SceneManager::PreviousScene()
{
	if (m_CurrentSceneIdx < 0)
	{
		m_CurrentSceneIdx = int(m_Scenes.size()-1);
	}
}

void cri::SceneManager::OpenScene(int sceneIdx)
{
	assert(sceneIdx > -1);
	assert(sceneIdx < m_Scenes.size());
	m_CurrentSceneIdx = sceneIdx;
}

cri::Scene& cri::SceneManager::GetScene(int sceneIdx)
{
	assert(sceneIdx > -1);
	assert(sceneIdx < m_Scenes.size());
	return *m_Scenes[sceneIdx];
}

cri::Scene& cri::SceneManager::GetCurrentScene()
{
	return GetScene(m_CurrentSceneIdx);
}

int cri::SceneManager::GetCurrentSceneIdx()
{
	return m_CurrentSceneIdx;
}
