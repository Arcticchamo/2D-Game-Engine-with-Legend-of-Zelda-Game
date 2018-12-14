#include "EngineCore.h"

#include "BackGroundMap.h"
#include "Camera.h"
#include "Player.h"
#include "Resources.h"
#include "VertexBuffer.h"
#include "VertexArray.h"

#include "MapSpriteLoader.h"
#include "CompressedMapLoader.h"

void EngineCore::StartEngine()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		throw std::exception();
	}

	m_window = SDL_CreateWindow("Triangle",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

	if (!SDL_GL_CreateContext(m_window))
	{
		throw std::exception();
	}

	if (glewInit() != GLEW_OK)
	{
		throw std::exception();
	}

	std::shared_ptr<MapSpriteLoader> spriteloads;
	spriteloads = std::make_shared<MapSpriteLoader>();
	std::shared_ptr<CompressedMapLoader> compmap;
	compmap = std::make_shared<CompressedMapLoader>();

	std::string FileLocation = "../SpriteSheets/Zelda_World_Map/Zelda_Overworld_Map";
	BackGroundMap map(FileLocation, compmap, spriteloads);


	Resources::Start("../shaders/simple.vert", "../shaders/simple.frag");
	m_player = std::make_shared<Player>("../Link.png");
	m_player->Start();

	

	std::shared_ptr<Camera> main_camera = std::make_shared<Camera>(CAMERA_TYPE::MAIN_CAMERA);
	main_camera->CreateCamera("Main Camera", SCREEN_WIDTH, SCREEN_HEIGHT);
	m_cameraList.push_back(main_camera);

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	
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
		SDL_GetWindowSize(m_window, &w, &h);
		glViewport(0, 0, w, h);

		for (size_t i = 0; i < m_cameraList.size(); i++)
		{
			m_cameraList.at(i)->UpdateCamera(SCREEN_WIDTH, SCREEN_HEIGHT);
		}

		Resources::SetUniform("in_ViewMat", glm::inverse(GetMainCamera()->GetViewMatrix()));
		Resources::SetUniform("in_ProjectionMat", GetMainCamera()->GetProjectionMatrix());

		m_player->Update();

		angle++;
		SDL_GL_SwapWindow(m_window);
	}
}

void EngineCore::DestroyEngine()
{
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}


std::shared_ptr<Camera> EngineCore::GetMainCamera()
{
	std::vector<std::shared_ptr<Camera> >::iterator it;

	for (it = m_cameraList.begin(); it != m_cameraList.end(); it++)
	{
		if ((*it)->getCameraType() == CAMERA_TYPE::MAIN_CAMERA)
		{
			return (*it);
		}
	}
	return NULL;
}