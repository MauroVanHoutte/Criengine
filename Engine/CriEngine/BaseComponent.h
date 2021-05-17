#pragma once
#include "GameObject.h"

class BaseComponent
{
public:
	BaseComponent(cri::GameObject* owner);
	virtual ~BaseComponent() = default;

	virtual void Update() {};
	virtual void FixedUpdate() {};
	virtual void LateUpdate() {};

	virtual void Render() const {};

protected:
	cri::GameObject* m_pOwner;
};