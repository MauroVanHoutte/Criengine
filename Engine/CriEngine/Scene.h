#pragma once
#include "SceneManager.h"
#include "SceneObject.h"
#include <memory>

namespace cri
{
	class SceneObject;
	class Scene
	{
		friend Scene& SceneManager::CreateScene(const std::string& name);
	public:
		void Add(const std::shared_ptr<SceneObject>& object);

		void Update();
		void FixedUpdate();
		void LateUpdate();
		void Render() const;

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

		void MoveObjectToFront(SceneObject* object);
		void MoveObjectToBack(SceneObject* object);


	private: 
		explicit Scene(const std::string& name);

		std::string m_Name;
		std::vector < std::shared_ptr<SceneObject>> m_Objects{};

		static unsigned int m_IdCounter; 
	};

}
