#include "EngineCore.h"

#include "BackGroundMap.h"
#include "Camera.h"
#include "CompressedMapLoader.h"
#include "MapSpriteLoader.h"
#include "Player.h"
#include "Resources.h"
#include "VertexBuffer.h"
#include "VertexArray.h"

std::shared_ptr<EngineCore> EngineCore::Init()
{
	std::shared_ptr<EngineCore> engine = std::make_shared<EngineCore>();
	engine->self = engine;

	engine->StartEngine();
	engine->UpdateEngine();
	engine->DestroyEngine();

	return engine;
}

void EngineCore::StartEngine()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		throw std::exception();
	}

	window = SDL_CreateWindow("Legend Of Zelda",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

	if (!SDL_GL_CreateContext(window))
	{
		throw std::exception();
	}

	if (glewInit() != GLEW_OK)
	{
		throw std::exception();
	}

	//Generate the shaders
	Resources::Start("../shaders/simple.vert", "../shaders/simple.frag");

	std::shared_ptr<Player> player = AddGameObject<Player>("../Link.png", "Player");


	//Setup the map loading classes 
	spriteLoader = std::make_shared<MapSpriteLoader>();
	compressedMapLoader = std::make_shared<CompressedMapLoader>();
	map = BackGroundMap::Init(
		"../SpriteSheets/Zelda_World_Map/Zelda_Overworld_Map", 
		compressedMapLoader, 
		spriteLoader);

	std::shared_ptr<Camera> camera = AddGameObject<Camera>(CAMERA_TYPE::MAIN_CAMERA, "Camera");
	camera->CreateCamera("Main Camera");

	//glEnable(GL_CULL_FACE);
	//glEnable(GL_DEPTH_TEST);
}

void EngineCore::UpdateEngine()
{
	bool quit = false;
	float angle = 0;

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

		int w = 0, h = 0;
		SDL_GetWindowSize(window, &w, &h);
		glViewport(0, 0, w, h);

		map->Display();


		for (size_t i = 0; i < gameObjectList.size(); i++)
		{
			gameObjectList.at(i)->Update();
		}

		angle++;
		SDL_GL_SwapWindow(window);
	}
}

void EngineCore::DestroyEngine()
{
	SDL_DestroyWindow(window);
	SDL_Quit();
}

std::shared_ptr<GameObject> EngineCore::GetMainCamera()
{
	std::vector<std::shared_ptr<GameObject> >::iterator it;
	for (it = gameObjectList.begin(); it != gameObjectList.end(); it++)
	{
		if ((*it)->GetTag() == "Camera")
		{
			if ((*it)->GetComponent<Camera>()->getCameraType() == CAMERA_TYPE::MAIN_CAMERA)
			{
				return (*it);
			}
		}	
	}
	return NULL;
}