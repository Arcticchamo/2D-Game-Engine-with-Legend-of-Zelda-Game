#include <exception>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <memory>
#include <SDL2/SDL.h>
#include <vector>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

class Camera;
class ShaderProgram;
class VertexArray;
class VertexBuffer;

class EngineCore
{
private:
	SDL_Window *m_window;

	std::vector < std::shared_ptr<Camera> > m_cameraList;


public:
	void StartEngine();
	void UpdateEngine();
	void DestroyEngine();

	std::shared_ptr<Camera> GetMainCamera();
};