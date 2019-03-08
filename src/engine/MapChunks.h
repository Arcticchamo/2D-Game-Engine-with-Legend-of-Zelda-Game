#include "GameObject.h"

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <array>
#include <memory>

class BackGroundMap;

class MapChunks : public GameObject
{
private:
	std::weak_ptr<BackGroundMap> backgroundMap;
	
	GLuint textureID;
	
	//Will need to create the mesh and store it here

public:

	MapChunks();
	MapChunks(std::shared_ptr<BackGroundMap> map);

	void CreateChunk(int widthChunks, int heightChunks, 
					int tileWidth, int tileHeight,
					int mapWidth, int mapHeight, 
					std::vector<int> uncompressedData);
	void CreateTexture();

	void RenderChunk();

};