#include "Component.h"
#include <memory>

class Mesh;
class Material;

class MeshRenderer : public Component
{
	std::weak_ptr<Mesh> mesh;
	std::shared_ptr<Material> material;
public:
	void Init(std::string path);
	void Update();
	void Render();
	void SetMesh(std::weak_ptr<Mesh> mesh);
	std::weak_ptr<Mesh> GetMesh();
	std::shared_ptr<Material> GetMaterial();
	~MeshRenderer();
};

