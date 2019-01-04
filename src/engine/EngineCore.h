#include <exception>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <memory>
#include <SDL2/SDL.h>
#include <vector>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

class BackGroundMap;
class Camera;
class Player;
class ShaderProgram;
class VertexArray;
class VertexBuffer;

class EngineCore
{
private:
	SDL_Window *m_window;

	std::vector < std::shared_ptr<Camera> > m_cameraList;
	//std::shared_ptr<ShaderProgram> m_shaderProgram;
	std::shared_ptr<Player> m_player;
	std::shared_ptr<BackGroundMap> map;

public:
	void StartEngine();
	void UpdateEngine();
	void DestroyEngine();

	std::shared_ptr<Camera> GetMainCamera();
};