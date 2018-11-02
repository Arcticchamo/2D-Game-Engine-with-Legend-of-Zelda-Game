#pragma once
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Object.h"
#include "Transform.h"

#include <GL/glew.h>
#include <memory>
#include <string>
#include <vector>

class Component;


class GameObject : public Object, public std::enable_shared_from_this<GameObject>
{
protected:
	
	std::string m_name;
	std::string m_textureFilePath;

	std::vector<std::shared_ptr<Component> > m_components;
	std::weak_ptr<Transform> m_transform;

public:

	GameObject() {}

	GameObject(std::string _texFileLoc)
	{
		m_textureFilePath = _texFileLoc;
	}

	virtual void Start() {};
	virtual void Update() {};
	virtual void Destroy() {};

	std::weak_ptr<Transform> GetTransform()
	{
		return std::weak_ptr<Transform>();
	}

	std::string GetTextureFilePath()
	{
		return m_textureFilePath;
	}


	template <class CompType>
	std::shared_ptr<CompType> AddComponent()
	{
		std::shared_ptr<CompType> Temp = std::make_shared<CompType>();
		m_components.push_back(Temp);
		//shared_from_this();
		Temp->SetObject(shared_from_this());
		Temp->Init();
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
