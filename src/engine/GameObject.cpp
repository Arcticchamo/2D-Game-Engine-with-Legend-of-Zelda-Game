#include "GameObject.h"

#include "Component.h"
#include "EngineCore.h"
#include "Resources.h"
#include "Screen.h"
#include "Transform.h"

#include <iostream>


void GameObject::Init()
{
	//TODO: transform = AddComponent<Transform>();
}

//Get and set the name and tag variables
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

//Iterate through each component and call their Update Functions
//Catch any errors that occur
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

//Iterate through each component and call their Render Functions
//Catch any errors that occur
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

std::weak_ptr<Transform> GameObject::GetTransfrom()
{
	return transform;
}

std::shared_ptr<GameObject> GameObject::GetCurrentCamera()
{
	return engineCore.lock()->GetCurrentCamera();
}

std::shared_ptr<Resources> GameObject::GetResources()
{
	return engineCore.lock()->GetResources();
}

std::shared_ptr<Screen> GameObject::GetScreen()
{
	return engineCore.lock()->GetScreen();
}