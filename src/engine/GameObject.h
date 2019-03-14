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
class EngineCore;

class GameObject : public Object, public std::enable_shared_from_this<GameObject>
{
	friend EngineCore;

protected:
	
	std::string name;
	std::string textureFilePath;

	std::string tag;

	std::vector<std::shared_ptr<Component> > components;
	std::weak_ptr<EngineCore> engineCore;
	std::weak_ptr<Transform> transform;

public:

	GameObject(){}

	virtual void Start() {};
	virtual void Update() {};

	std::weak_ptr<Transform> GetTransform()
	{
		return std::weak_ptr<Transform>();
	}
	std::string GetTextureFilePath()
	{
		return textureFilePath;
	}
	std::string GetTag() { return tag; }

	template <class CompType>
	std::shared_ptr<CompType> AddComponent()
	{
		std::shared_ptr<CompType> Temp = std::make_shared<CompType>();
		components.push_back(Temp);
		//shared_from_this();
		Temp->SetObject(shared_from_this());
		Temp->Init();
		return Temp;
	}

	template <class CompType>
	std::shared_ptr<CompType> GetComponent()
	{
		for (size_t i = 0; i < components.size(); i++)
		{
			std::shared_ptr<CompType> c = std::dynamic_pointer_cast<CompType>(components.at(i));

			if (c)
			{
				return c;
			}
		}
		return std::shared_ptr<CompType>(); 
	}

	virtual ~GameObject() {};
};

#endif
