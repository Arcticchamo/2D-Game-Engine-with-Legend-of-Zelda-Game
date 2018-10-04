#include "Component.h"

#include <memory>

class Mesh;

class MeshRenderer : public Component
{
private:
	std::weak_ptr<Mesh> m_mesh;

public:
	MeshRenderer();

	void Start();
	void Update();
	void Destroy();
	
	~MeshRenderer();
};