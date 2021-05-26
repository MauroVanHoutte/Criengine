#pragma once
#include <string>
#include "Transform.h"
#include "SceneObject.h"
#include "Texture2D.h"
#include <map>

class BaseComponent;

namespace cri
{
	class Texture2D;
	class GameObject final : public SceneObject
	{
	public:
		void Update() override;
		void FixedUpdate() override;
		void LateUpdate() override;
		void Render() const override;

		void SetPosition(float x, float y);

		bool AddComponent(const std::string& name, BaseComponent* component);
		bool RemoveComponent(const std::string& name);
		std::map<std::string, BaseComponent*>& GetComponents();

		template<typename T>
		T* GetComponent()
		{
			for (auto it = m_ComponentMap.begin(); it != m_ComponentMap.end(); it++)
			{
				T* comp = dynamic_cast<T*>(it->second);
				if (comp != nullptr)
				{
					return comp;
				}
			}
			return nullptr;
		}


		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		Transform m_Transform;

	private:
		std::map<std::string, BaseComponent*> m_ComponentMap;
	};

}
