#include <GL/glew.h>
#include <glm/glm.hpp>
#include <array>
#include <memory>
#include <vector>

class BackGroundMap;
class Texture;

//TODO: UPDATE THIS 

class MapChunks
{
private:
	static const int rgbDataSize = 512 * 3 * 512;
	static const int chunkWidth = 512;
	static const int chunkHeight = 512;
	std::weak_ptr<BackGroundMap> backgroundMap;
	std::shared_ptr<Texture> texture;
	glm::vec3 position;
public:
	MapChunks(std::shared_ptr<BackGroundMap> map);
	void CreateChunk(int widthChunks, int heightChunks, 
					int tileWidth, int tileHeight,
					int mapWidth, int mapHeight, 
					std::vector<int> uncompressedData);
	void CreateTexture(std::array <unsigned char, rgbDataSize> &rgbData);
	void AssignInformation(int tileWidth, int tileHeight, int tileIndex, int tileX, int tileY, int numberOfTilesInChunksX, std::array <unsigned char, rgbDataSize> &rgbData);
	std::shared_ptr<Texture> GetTexture() { return texture; }
	glm::vec3 GetPosition() { return position; }
};