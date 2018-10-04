#include "GameObject.h"
#include "Mesh.h"
#include "MeshRenderer.h"


MeshRenderer::MeshRenderer()
{
}

void MeshRenderer::Start()
{
	m_mesh = m_gameObject.lock()->GetComponent<Mesh>();
}

void MeshRenderer::Update()
{
}

void MeshRenderer::Destroy()
{
}

MeshRenderer::~MeshRenderer()
{
}