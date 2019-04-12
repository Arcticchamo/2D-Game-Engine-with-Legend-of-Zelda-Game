#include "GameObject.h"

#include "Component.h"
#include "EngineCore.h"
#include "Resources.h"
#include "Screen.h"
#include "Transform.h"

#include <iostream>


void GameObject::Init()
{
	transform = AddComponent<Transform>();
}

std::string GameObject::GetTag()
{
	return tag;
}

std::string GameObject::GetName()
{
	return name;
}

void GameObject::SetTag(std::string tag)
{
	this->tag = tag;
}

void GameObject::SetName(std::string name)
{
	this->name = name;
}

void GameObject::Update()
{
	for (std::vector<std::shared_ptr<Component>>::iterator it = components.begin(); it != components.end(); it++)
	{
		try 
		{
			(*it)->Update();
		}
		catch(std::exception &e)
		{
			std::cout << e.what() << std::endl;
		}
	}
}

void GameObject::Render()
{
	for (std::vector<std::shared_ptr<Component>>::iterator it = components.begin(); it != components.end(); it++)
	{
		try
		{
			(*it)->Render();
		}
		catch (std::exception &e)
		{
			std::cout << e.what() << std::endl;
		}
	}
}

std::weak_ptr<EngineCore> GameObject::GetEngineCore()
{
	return engineCore;
}

std::shared_ptr<GameObject> GameObject::GetCurrentCamera()
{
	return engineCore.lock()->GetCurrentCamera();
}