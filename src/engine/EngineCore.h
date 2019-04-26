#include "GameObject.h"

#include <exception>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <memory>
#include <vector>

class Camera;
class CompressedMapSpriteLoader;
class CompressedMapTextLoader;
class GameObject;
class Resources;
class Screen;

class EngineCore
{
private:
	//List of every GameObject in the main Scene
	std::vector<std::shared_ptr<GameObject> > gameObjectList;
	//A reference to each camera in the scene
	std::vector<std::weak_ptr<GameObject> > cameraList;
	//A reference to itself. Used for setting GameObject references
	std::weak_ptr<EngineCore> self;
	//Current Camera references the current camera being rendered in the scene
	std::weak_ptr<GameObject> currentCamera;
	std::shared_ptr<CompressedMapSpriteLoader> compressedMapSpriteLoader;
	std::shared_ptr<CompressedMapTextLoader> compressedMapTextLoader;
	std::shared_ptr<Resources> resources;
	std::shared_ptr<Screen> screen;

	//Called when Engine is started. Loads any prerequisites
	void InitialiseEngine();
public:
	friend class Camera; //Linked so there is access to the CameraList Vector

	//Accessed inside of main(), returning a reference to the engine
	static std::shared_ptr<EngineCore> Init();
	//Called Every Frame - Main GameLoop stored in this function
	void UpdateEngine();
	//Anything that needs to happen when the engine is closing. Currently Depricated TODO: SEE IF NEEDED
	void DestroyEngine();

	//Getters Designed for obtaining key classes within the engine
	std::shared_ptr<GameObject> GetCurrentCamera();
	std::shared_ptr<CompressedMapSpriteLoader> GetMapSpriteLoader();
	std::shared_ptr<CompressedMapTextLoader> GetMapTextLoader();
	std::shared_ptr<Resources> GetResources();
	std::shared_ptr<Screen> GetScreen();

	//AddGameobject functions and templates designed for different situations.
	//It creates a GameObject, then adds any components passed in (such as Player)
	std::shared_ptr<GameObject> AddGameObject();

	template <class goType>
	std::shared_ptr<GameObject> AddGameObject()
	{
		std::shared_ptr<GameObject> go = AddGameObject();
		go->AddComponent<goType>();
		return go;
	}

	template <class goType, class A>
	std::shared_ptr<GameObject> AddGameObject(A a)
	{
		std::shared_ptr<GameObject> go = AddGameObject();
		go->AddComponent<goType>(a);
		return go;
	}

	template <class goType, class A, class B>
	std::shared_ptr<GameObject> AddGameObject(A a, B b)
	{
		std::shared_ptr<GameObject> go = AddGameObject();
		go->AddComponent<goType>(a, b);
		return go;
	}

	template <class goType, class A, class B, class C>
	std::shared_ptr<GameObject> AddGameObject(A a, B b, C c)
	{
		std::shared_ptr<GameObject> go = AddGameObject();
		go->AddComponent<goType>(a, b, c);
		return go;
	}
};