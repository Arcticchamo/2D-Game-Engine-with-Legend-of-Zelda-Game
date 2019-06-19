#include "Component.h"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <array>
#include <memory>
#include <vector>

class BackGroundMap;
class MeshRenderer;
class Texture;


class MapChunks : public Component
{
private:
	static const int rgbaDataSize = 512 * 4 * 512;
	static const int chunkWidth = 512;
	static const int chunkHeight = 512;
	std::weak_ptr<BackGroundMap> backgroundMap;

	std::weak_ptr<MeshRenderer> meshRenderer; //Stores the texture and renders it
	std::weak_ptr<Transform> transform; //stores the position, rotation and scale.

	std::shared_ptr<Texture> texture; //Texture to store the map 

	void CreateTexture(std::vector<unsigned char> &rgbaData);
	void AssignInformation(int tileWidth, int tileHeight, int tileIndex, int tileX, int tileY, int numberOfTilesInChunksX, std::vector<unsigned char> &rgbaData);
	void AssignBlackInformation(int tileWidth, int tileHeight, int tileX, int tileY, int numberOfTilesInChunksX, std::vector<unsigned char> &rgbaData);
public:
	void Init(std::shared_ptr<BackGroundMap> map);

	void CreateChunk(int widthChunks, int heightChunks, 
					int tileWidth, int tileHeight,
					int mapWidth, int mapHeight, 
					std::vector<int> uncompressedTxtData);
	
};   