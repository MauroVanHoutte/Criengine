#pragma once
#include "Transform.h"
#include "SceneObject.h"
#include "Texture2D.h"
#include <map>

class BaseComponent;

namespace dae
{
	class Texture2D;
	class GameObject : public SceneObject
	{
	public:
		void Update() override;
		void FixedUpdate() override;
		void LateUpdate() override;
		void Render() const override;

		void SetTexture(const std::string& filename);
		void SetPosition(float x, float y);

		bool AddComponent(const std::string& name, BaseComponent* component);
		bool RemoveComponent(const std::string& name);
		std::map<std::string, BaseComponent*>& GetComponents();


		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		Transform m_Transform;
		std::map<std::string, BaseComponent*> m_ComponentMap;
		std::shared_ptr<Texture2D> m_Texture;
	};
}
