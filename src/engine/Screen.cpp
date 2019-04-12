#include "Screen.h"

#include <GL/glew.h>

Screen::Screen()
{

}

Screen::Screen(int screenWidth, int screenHeight)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		throw std::exception();
	}

	this->screenWidth = screenWidth;
	this->screenHeight = screenHeight;

	window = SDL_CreateWindow("Legend Of Zelda",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		screenWidth, screenHeight, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

	if (!SDL_GL_CreateContext(window))
	{
		throw std::exception();
	}
}

int Screen::GetScreenWidth()
{
	return screenWidth;
}

int Screen::GetScreenHeight()
{
	return screenHeight;
}

glm::mat4 Screen::GetProjectionMatrix()
{
	return glm::ortho(0.0f, (float)screenWidth, (float)screenHeight, 0.0f, -1.0f, 1.0f);
}

void Screen::UpdateViewPort()
{
	SDL_GetWindowSize(window, &screenWidth, &screenHeight);
	glViewport(0, 0, screenWidth, screenHeight);
}

void Screen::SwapWindow()
{
	SDL_GL_SwapWindow(window);
}

Screen::~Screen()
{
	SDL_DestroyWindow(window);
	SDL_Quit();
}