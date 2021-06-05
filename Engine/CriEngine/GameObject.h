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

		bool AddComponent(BaseComponent* component);
		bool RemoveComponent(BaseComponent* component);
		std::vector<BaseComponent*>& GetComponents();

		template<typename T>
		T* GetComponent()
		{
			for (auto it = m_Components.begin(); it != m_Components.end(); it++)
			{
				T* comp = dynamic_cast<T*>(*it);
				if (comp != nullptr)
				{
					return comp;
				}
			}
			return nullptr;
		}

		template<typename T>
		std::vector<T*> GetComponents()
		{
			std::vector<T*> TComponents;
			for (auto it = m_Components.begin(); it != m_Components.end(); it++)
			{
				T* comp = dynamic_cast<T*>(*it);
				if (comp != nullptr)
				{
					TComponents.push_back(comp);
				}
			}
			return TComponents;
		}


		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		Transform m_Transform;

	private:
		std::vector<BaseComponent*> m_Components;
	};

}
