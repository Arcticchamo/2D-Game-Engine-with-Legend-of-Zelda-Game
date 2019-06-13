#include "GameObject.h"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <array>
#include <memory>
#include <vector>

class BackGroundMap;
class MeshRenderer;
class Texture;


class MapChunks : public GameObject
{
private:
	static const int rgbDataSize = 512 * 3 * 512;
	static const int chunkWidth = 512;
	static const int chunkHeight = 512;
	std::weak_ptr<BackGroundMap> backgroundMap;

	std::weak_ptr<MeshRenderer> meshRenderer; //Stores the texture and renders it
	//std::weak_ptr<Transform> transform; //stores the position, rotation and scale.

	void CreateTexture(std::array <unsigned char, rgbDataSize> &rgbData);
	void AssignInformation(int tileWidth, int tileHeight, int tileIndex, int tileX, int tileY, int numberOfTilesInChunksX, std::array <unsigned char, rgbDataSize> &rgbData);
	void AssignBlackInformation();
public:
	MapChunks(std::shared_ptr<BackGroundMap> map);

	void CreateChunk(int widthChunks, int heightChunks, 
					int tileWidth, int tileHeight,
					int mapWidth, int mapHeight, 
					std::vector<int> uncompressedTxtData);
	
};