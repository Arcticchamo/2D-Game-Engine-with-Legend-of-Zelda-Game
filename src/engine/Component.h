#pragma once
#ifndef COMPONENT_H
#define COMPONENT_H

#include "Object.h"

#include <memory>

class GameObject;

class Component : public Object, public std::enable_shared_from_this<Component>
{
protected:
	std::weak_ptr<GameObject> m_gameObject;
	
public:
	virtual void Start() {};
	virtual void Update() {};
	virtual void Destroy() {};

	void SetObject(std::weak_ptr<GameObject> _object)
	{
		m_gameObject = _object;
	}

	virtual void Init() {};

	virtual ~Component() {};
};

#endif