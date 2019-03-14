#include <exception>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <memory>
#include <SDL2/SDL.h>
#include <vector>

#include "GameObject.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

class BackGroundMap;
class Camera;
class CompressedMapLoader;
class MapSpriteLoader;
class Player;
class ShaderProgram;
class VertexArray;
class VertexBuffer;

class EngineCore
{
private:
	SDL_Window *window;

	std::vector < std::shared_ptr<GameObject> > gameObjectList;
	//std::vector < std::shared_ptr<Camera> > cameraList;

	std::weak_ptr<EngineCore> self;
	std::shared_ptr<Player> player;
	std::shared_ptr<BackGroundMap> map;

	std::shared_ptr<MapSpriteLoader> spriteLoader;
	std::shared_ptr<CompressedMapLoader> compressedMapLoader;
public:

	static std::shared_ptr<EngineCore> Init();
	void StartEngine();
	void UpdateEngine();
	void DestroyEngine();

	int GetScreenWidth() { return SCREEN_WIDTH; }
	int GetScreenHeight() { return SCREEN_HEIGHT; }

	std::shared_ptr<GameObject> GetMainCamera();

	template <class goType>
	std::shared_ptr<goType> AddGameObject()
	{
		std::shared_ptr<goType> gameObject = std::make_shared<goType>();
		gameObject->engineCore = self.lock();
		gameObjectList.push_back(gameObject);
		gameObject->Init();
		return gameObject;
	}

	template <class goType, class A>
	std::shared_ptr<goType> AddGameObject(A a)
	{
		std::shared_ptr<goType> gameObject = std::make_shared<goType>();
		gameObject->engineCore = self.lock();
		gameObjectList.push_back(gameObject);
		gameObject->Init(a);
		return gameObject;
	}

	template <class goType, class A, class B>
	std::shared_ptr<goType> AddGameObject(A a, B b)
	{
		std::shared_ptr<goType> gameObject = std::make_shared<goType>();
		gameObject->engineCore = self.lock();
		gameObjectList.push_back(gameObject);
		gameObject->Init(a, b);
		return gameObject;
	}

};