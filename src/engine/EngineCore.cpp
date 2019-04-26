#include "Camera.h"
#include "CompressedMapSpriteLoader.h"
#include "CompressedMapTextLoader.h"
#include "EngineCore.h"
#include "GameObject.h"
#include "Resources.h"
#include "Screen.h"

//Called when creating a EngineCore Object
//Creates a pointer, then initialises itself
std::shared_ptr<EngineCore> EngineCore::Init()
{
	std::shared_ptr<EngineCore> engine = std::make_shared<EngineCore>();
	engine->self = engine;
	engine->InitialiseEngine();
	return engine;
}

//Any classes that need initialising within the engine gets created here
void EngineCore::InitialiseEngine()
{
	//Creates the main Window (SDL)
	screen = std::make_shared<Screen>(800, 600);

	//Init GL
	if (glewInit() != GLEW_OK)
	{
		throw std::exception();
	}
	compressedMapSpriteLoader = std::make_shared<CompressedMapSpriteLoader>();
	compressedMapTextLoader = std::make_shared<CompressedMapTextLoader>();
	resources = std::make_shared<Resources>();
}

//Called every frame of the game
//Handles real time elements such as GameObjects and Windows
void EngineCore::UpdateEngine()
{
	bool quit = false;

	while (!quit)
	{
		SDL_Event event = { 0 };

		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				quit = true;
			}
		}
		glClearColor(1.0f, 0.95f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		screen->UpdateViewPort();

		for (size_t i = 0; i < gameObjectList.size(); i++)
		{
			gameObjectList.at(i)->Update();
		}

		//Rendering through each camera perspective to render the game
		//from all camera - incase the scene has multiple cameras
		for (size_t c = 0; c < cameraList.size(); c++)
		{
			currentCamera = cameraList.at(c);
			for (size_t i = 0; i < gameObjectList.size(); i++)
			{
				gameObjectList.at(i)->Render();
			}
		}

		screen->SwapWindow();
	}
}

void EngineCore::DestroyEngine()
{}

//Returns the mapSpriteLoader smart ptr 
//throws an exception if an error occurs
std::shared_ptr<CompressedMapSpriteLoader> EngineCore::GetMapSpriteLoader()
{
	try
	{
		return compressedMapSpriteLoader;
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
}

//Returns the mapTextLoader smart ptr 
//throws an exception if an error occurs
std::shared_ptr<CompressedMapTextLoader> EngineCore::GetMapTextLoader()
{
	try
	{
		return compressedMapTextLoader;
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
}

//Returns the resources smart ptr 
//throws an exception if an error occurs
std::shared_ptr<Resources> EngineCore::GetResources()
{
	try
	{
		return resources;
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
}

//Returns the screen smart ptr 
//throws an exception if an error occurs
std::shared_ptr<Screen> EngineCore::GetScreen()
{
	try
	{
		return screen;
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
}

//Returns the current camera
std::shared_ptr<GameObject> EngineCore::GetCurrentCamera()
{
	try
	{
		return currentCamera.lock();
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
}

//Creates a new GameObject, assigns parameters and pushes it into the GameObjectList vector
std::shared_ptr<GameObject> EngineCore::AddGameObject()
{
	std::shared_ptr<GameObject> go = std::make_shared<GameObject>();
	go->engineCore = self.lock();
	go->SetName("Name");
	go->SetTag("Tag");
	gameObjectList.push_back(go);
	return go;
}