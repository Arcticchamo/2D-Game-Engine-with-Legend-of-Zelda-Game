#pragma once
#ifndef COMPONENT_H
#define COMPONENT_H

#include "Object.h"
#include <memory>

class EngineCore;
class GameObject;
class Resources;
class Screen;
class Transform;

//Base class for all components
class Component : public Object, public std::enable_shared_from_this<Component>
{
protected:
	std::weak_ptr<GameObject> gameObject;
public:
	//Purely for Children classes to inherit
	virtual void Init() {};
	virtual void Update() {};
	virtual void Render() {};

	//Function that is called when adding the component to a GameObject
	void SetGameObject(std::weak_ptr<GameObject> GameObject);

	//A part of the engines sub system of connectivity
	std::weak_ptr<GameObject> GetGameObject();
	std::shared_ptr<Resources> GetResources();
	std::shared_ptr<Screen> GetScreen();
	std::shared_ptr<Transform> GetTransfrom();
	std::weak_ptr<EngineCore> GetEngineCore();
	std::shared_ptr<GameObject> GetCurrentCamera();

	virtual ~Component() {};
};

#endif