#include "EngineCore.h"

#include "Camera.h"
#include "Player.h"
#include "Resources.h"
#include "ShaderProgram.h"
#include "VertexBuffer.h"
#include "VertexArray.h"


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


	m_player = std::make_shared<Player>("../GC.png");
	m_player->Start();

	//m_shaderProgram = std::make_shared<ShaderProgram>("../shaders/simple.vert", "../shaders/simple.frag");
	Resources::Start("../shaders/simple.vert", "../shaders/simple.frag");

	std::shared_ptr<Camera> main_camera = std::make_shared<Camera>(CAMERA_TYPE::MAIN_CAMERA);
	main_camera->CreateCamera("Main Camera", SCREEN_WIDTH, SCREEN_HEIGHT);
	m_cameraList.push_back(main_camera);
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

		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		int w = 0, h = 0;
		SDL_GetWindowSize(m_window, &w, &h);
		glViewport(0, 0, w, h);


		glm::mat4 modelMatrix(1.0f);
		modelMatrix = glm::translate(modelMatrix, glm::vec3((SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2), 0.0f));
		modelMatrix = glm::rotate(modelMatrix, glm::radians(angle), glm::vec3(0, 0, 1));
		modelMatrix = glm::translate(modelMatrix, glm::vec3(-50, -50, 0.0f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(100, 100, 1));

		//m_shaderProgram->setUniform("in_ModelMat", modelMatrix);
		Resources::SetUniform("in_ModelMat", modelMatrix);

		//m_shaderProgram->setUniform("in_ViewMat", GetMainCamera()->GetViewMatrix());
		//m_shaderProgram->setUniform("in_ProjectionMat", GetMainCamera()->GetProjectionMatrix());

		Resources::SetUniform("in_ViewMat", GetMainCamera()->GetViewMatrix());
		Resources::SetUniform("in_ProjectionMat", GetMainCamera()->GetProjectionMatrix());

		//m_shaderProgram->Draw(m_player->GetVAO());

		m_player->Render();

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