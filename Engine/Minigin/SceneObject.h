#pragma once
#include "Subject.h"
namespace dae
{
	class SceneObject : public Subject
	{
	public:
		virtual void Update() = 0;
		virtual void FixedUpdate() = 0;
		virtual void LateUpdate() = 0;
		virtual void Render() const = 0;

	protected:
		SceneObject() = default;
		virtual ~SceneObject() = default;
		SceneObject(const SceneObject& other) = delete;
		SceneObject(SceneObject&& other) = delete;
		SceneObject& operator=(const SceneObject& other) = delete;
		SceneObject& operator=(SceneObject&& other) = delete;
	};
}
