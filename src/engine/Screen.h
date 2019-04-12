#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <SDL2/SDL.h>
#include <exception>

class Screen
{
private:
	int screenWidth;
	int screenHeight;
	SDL_Window *window;

public:
	Screen();
	Screen(int screenWidth, int screenHeight);
	int GetScreenWidth();
	int GetScreenHeight();
	glm::mat4 GetProjectionMatrix();
	void UpdateViewPort();
	void SwapWindow();

	~Screen();
};