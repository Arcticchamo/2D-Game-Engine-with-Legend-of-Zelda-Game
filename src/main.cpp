#include <memory>

#include "EngineCore.h"

int main(int argc, char *argv[])
{
	std::shared_ptr<EngineCore> engine = std::make_shared<EngineCore>();

	engine->StartEngine();
	engine->UpdateEngine();
	engine->DestroyEngine();	 

	 return 0;
}
