#pragma once
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Object.h"

#include <memory>
#include <string>
#include <vector>

class Component;
class Transform;

class GameObject : public Object, std::enable_shared_from_this<GameObject>
{
private:
	
	std::string m_name;
	
	std::vector<std::shared_ptr<Component> > m_components;
	std::weak_ptr<Transform> m_transform;

public:
	virtual void Start() {};
	virtual void Update() {};
	virtual void Destroy() {};

	std::weak_ptr<Transform> GetTransform()
	{
		return std::weak_ptr<Transform>();
	}

	//GameObject* GetGameObject();

	template <class CompType>
	std::weak_ptr<CompType> AddComponent()
	{
		std::shared_ptr<CompType> Temp = std::make_shared<CompType>();
		m_components.push_back(Temp);
		Temp->setObject(shared_from_this());
		return Temp;
	}

	template <class CompType>
	std::shared_ptr<CompType> GetComponent()
	{
		for (size_t i = 0; i < m_components.size(); i++)
		{
			std::shared_ptr<CompType> c = std::dynamic_pointer_cast<CompType>(m_components.at(i));

			if (c)
			{
				return c;
			}
		}
		return std::shared_ptr<CompType>(); //throw
	}

	virtual ~GameObject() {};
};

#endif