#include <memory>

#include "EngineCore.h"

int main(int argc, char *argv[])
{
	std::shared_ptr<EngineCore> engine = EngineCore::Init();
	 return 0;
}
