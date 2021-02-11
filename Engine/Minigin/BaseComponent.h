#pragma once
#include "GameObject.h"

class BaseComponent
{
public:
	BaseComponent(dae::GameObject* owner);
	virtual ~BaseComponent() = default;

	virtual void Update() {};
	virtual void FixedUpdate() {};
	virtual void LateUpdate() {};

	virtual void Render() const {};

protected:
	dae::GameObject* m_pOwner;
};