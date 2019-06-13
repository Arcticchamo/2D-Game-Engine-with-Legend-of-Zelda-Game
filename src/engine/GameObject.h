#pragma once
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Object.h"
#include <GL/glew.h>
#include <memory>
#include <string>
#include <vector>

class Component;
class EngineCore;
class Screen;
class Resources;
class Transform;

class GameObject : public Object, public std::enable_shared_from_this<GameObject>
{
	friend EngineCore;
protected:
	//Inherited members 
	std::string name;
	std::string tag;
	//A list of each component attached to the GameObject
	//This is looped through twice per frame 
	//Once for Update, Once for Render
	std::vector<std::shared_ptr<Component>> components;
	std::weak_ptr<EngineCore> engineCore;
	std::weak_ptr<Transform> transform;
public:
	GameObject() {}
	void Init();
	void Update();
	void Render();

	//Tag and Name are used for searching through existing objects. TODO: INTEGRATE SEARCH OPTIONS
	std::string GetTag();
	std::string GetName();
	void SetTag(std::string tag);
	void SetName(std::string name);

	//Getters that access the engineCore and return the object ptrs
	std::weak_ptr<EngineCore> GetEngineCore();
	std::weak_ptr<Transform> GetTransfrom();
	std::shared_ptr<GameObject> GetCurrentCamera();
	std::shared_ptr<Resources> GetResources();
	std::shared_ptr<Screen> GetScreen();

	//Add Component takes a Component and pushes it into the components vector
	//It passes the current GameObject into the component as a shared ptr
	//and Initialises the Component
	//Multiple iterations exist for Addcomponent for additional parameters if needed
	template <class CompType>
	std::shared_ptr<CompType> AddComponent()
	{
		std::shared_ptr<CompType> comp = std::make_shared<CompType>();
		components.push_back(comp);
		comp->SetGameObject(shared_from_this());
		comp->Init();
		return comp;
	}

	template <class CompType, class A>
	std::shared_ptr<CompType> AddComponent(A a)
	{
		std::shared_ptr<CompType> comp = std::make_shared<CompType>();
		components.push_back(comp);
		comp->SetGameObject(shared_from_this());
		comp->Init(a);
		return comp;
	}

	template <class CompType, class A, class B>
	std::shared_ptr<CompType> AddComponent(A a, B b)
	{
		std::shared_ptr<CompType> comp = std::make_shared<CompType>();
		components.push_back(comp);
		comp->SetGameObject(shared_from_this());
		comp->Init(a, b);
		return comp;
	}

	template <class CompType, class A, class B, class C>
	std::shared_ptr<CompType> AddComponent(A a, B b, C c)
	{
		std::shared_ptr<CompType> comp = std::make_shared<CompType>();
		components.push_back(comp);
		comp->SetGameObject(shared_from_this());
		comp->Init(a, b, c);
		return comp;
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
