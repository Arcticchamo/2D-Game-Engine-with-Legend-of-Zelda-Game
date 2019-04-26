#include <memory>
#include "engine/engine.h"
#include "Player.h"

void CreateGameObjects(std::shared_ptr<EngineCore> engine);

int main(int argc, char *argv[])
{
	std::shared_ptr<EngineCore> engine = EngineCore::Init();
	
	CreateGameObjects(engine);

	engine->UpdateEngine();

	engine->DestroyEngine();
	return 0;
}

void CreateGameObjects(std::shared_ptr<EngineCore> engine)
{
	std::shared_ptr<GameObject> main_camera = engine->AddGameObject<Camera>();
	std::shared_ptr<GameObject> player = engine->AddGameObject<Player>();
	std::shared_ptr<GameObject> bgm = engine->AddGameObject<BackGroundMap>("../Resources/Maps/Zelda_World_Map/Zelda_World_Map");
}