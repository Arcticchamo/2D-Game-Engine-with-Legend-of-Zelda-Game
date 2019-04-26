#include "Component.h"
#include "CompressedMapSpriteLoader.h"
#include "CompressedMapTextLoader.h"
#include "EngineCore.h"
#include "GameObject.h"
#include "Resources.h"
#include "Screen.h"
#include "Transform.h"

void Component::SetGameObject(std::weak_ptr<GameObject> GameObject)
{
	gameObject = GameObject;
}

std::shared_ptr<CompressedMapSpriteLoader> Component::GetMapSpriteLoader()
{
	return gameObject.lock()->GetEngineCore().lock()->GetMapSpriteLoader();
}

std::shared_ptr<CompressedMapTextLoader> Component::GetMapTextLoader()
{
	return gameObject.lock()->GetEngineCore().lock()->GetMapTextLoader();
}

std::shared_ptr<GameObject> Component::GetCurrentCamera()
{
	return gameObject.lock()->GetCurrentCamera();
}

std::shared_ptr<Resources> Component::GetResources()
{
	return gameObject.lock()->GetEngineCore().lock()->GetResources();
}

std::shared_ptr<Screen> Component::GetScreen()
{
	return gameObject.lock()->GetEngineCore().lock()->GetScreen();
}

std::shared_ptr<Transform> Component::GetTransfrom()
{
	return gameObject.lock()->GetComponent<Transform>();
}

std::weak_ptr<EngineCore> Component::GetEngineCore()
{
	return gameObject.lock()->GetEngineCore();
}

std::weak_ptr<GameObject> Component::GetGameObject()
{
	return gameObject;
}